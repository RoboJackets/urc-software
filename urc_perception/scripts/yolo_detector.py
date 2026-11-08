
import ast
import cv2
from cv_bridge import CvBridge, CvBridgeError
import numpy as np
import onnxruntime as ort
import rclpy
from rclpy.node import Node
from rclpy.qos import HistoryPolicy, QoSProfile, ReliabilityPolicy
from sensor_msgs.msg import Image
from urc_msgs.msg import DetectionBoundingBox

LETTERBOX_PAD = 114
DEBUG_COLOR = (0, 255, 0)

def letterbox(image, input_width, input_height):

    height, width = image.shape[:2]
    scale = min(input_width / width, input_height / height)
    new_width, new_height = max(1, round(width * scale)), max(1, round(height * scale))
    pad_x, pad_y = (input_width - new_width) // 2, (input_height - new_height) // 2
    canvas = np.full((input_height, input_width, 3), LETTERBOX_PAD, dtype=np.uint8)
    canvas[pad_y:pad_y + new_height, pad_x:pad_x + new_width] = cv2.resize(image, (new_width, new_height), interpolation=cv2.INTER_LINEAR)
    rgb = cv2.cvtColor(canvas, cv2.COLOR_BGR2RGB)
    tensor = np.ascontiguousarray(rgb.transpose(2, 0, 1)[np.newaxis], dtype=np.float32) / 255.0
    return tensor, scale, pad_x, pad_y


def decode(output, scale, pad_x, pad_y, image_shape, conf_threshold, iou_threshold, max_det):

    predictions = output[0]
    if predictions.shape[0] < predictions.shape[1]:
        predictions = predictions.T #[anchors, 4 + classes]

    scores = predictions[:, 4:]
    class_ids = scores.argmax(axis=1)
    confidences = scores[np.arange(len(scores)), class_ids]
    keep = confidences >= conf_threshold
    boxes, class_ids, confidences = predictions[keep, :4], class_ids[keep], confidences[keep]

    if len(boxes) == 0:
        return []

    height, width = image_shape[:2]
    x1 = np.clip((boxes[:, 0] - boxes[:, 2] / 2 - pad_x) / scale, 0, width)
    y1 = np.clip((boxes[:, 1] - boxes[:, 3] / 2 - pad_y) / scale, 0, height)
    x2 = np.clip((boxes[:, 0] + boxes[:, 2] / 2 - pad_x) / scale, 0, width)
    y2 = np.clip((boxes[:, 1] + boxes[:, 3] / 2 - pad_y) / scale, 0, height)

    offset = class_ids * (max(width, height) + 1)
    nms_boxes = np.stack([x1 + offset, y1 + offset, x2 - x1, y2 - y1], axis=1)
    indices = cv2.dnn.NMSBoxes(nms_boxes.tolist(), confidences.tolist(), conf_threshold, iou_threshold)
    indices = np.array(indices, dtype=int).flatten()[:max_det]

    return [(float(x1[i]), float(y1[i]), float(x2[i]), float(y2[i]), float(confidences[i]), int(class_ids[i])) for i in indices]


class YoloDetector(Node):

    def __init__(self):
        super().__init__('yolo_detector')

        model_path = self.declare_parameter('model_path', '../models/model.onnx').value

        # Topics for reading camera data and outputting detections
        image_topic = self.declare_parameter('image_topic', '/camera/image_raw').value
        detections_topic = self.declare_parameter('detections_topic', '/yolo/detections').value
        debug_topic = self.declare_parameter('debug_topic', '/yolo/image_debug').value

        publish_debug = self.declare_parameter('publish_debug', True).value
        self.conf_threshold = float(self.declare_parameter('confidence_threshold', 0.25).value)

        self.iou_threshold = float(self.declare_parameter('iou_threshold', 0.45).value)
        self.max_det = int(self.declare_parameter('max_detections', 100).value)

        use_cuda = self.declare_parameter('use_cuda', False).value

        providers = ['CPUExecutionProvider']

        if use_cuda:
            providers.insert(0, 'CUDAExecutionProvider')

        self.session = ort.InferenceSession(model_path, providers=providers)
        model_input = self.session.get_inputs()[0]
        self.input_name = model_input.name
        self.input_height, self.input_width = model_input.shape[2], model_input.shape[3]
        if not isinstance(self.input_height, int) or not isinstance(self.input_width, int):
            raise ValueError('Model needs a fixed input size; export it with dynamic=False')

        names = self.session.get_modelmeta().custom_metadata_map.get('names')
        self.class_names = ast.literal_eval(names) if names else {}

        self.bridge = CvBridge()

        sensor_qos = QoSProfile(reliability=ReliabilityPolicy.BEST_EFFORT, history=HistoryPolicy.KEEP_LAST, depth=1)

        self.create_subscription(Image, image_topic, self.on_image, sensor_qos)
        self.detections_pub = self.create_publisher(DetectionBoundingBox, detections_topic, 10)
        self.debug_pub = self.create_publisher(Image, debug_topic, 1) if publish_debug else None

        self.get_logger().info(
            f'Loaded {model_path} ({self.input_width}x{self.input_height}, '
            f'{len(self.class_names)} classes, {self.session.get_providers()[0]}); '
            f'listening on {image_topic}')

    def on_image(self, msg):
        try:
            image = self.bridge.imgmsg_to_cv2(msg, desired_encoding='bgr8')
        except CvBridgeError as error:
            self.get_logger().warn(f'Dropping image: {error}', throttle_duration_sec=2.0)
            return

        tensor, scale, pad_x, pad_y = letterbox(image, self.input_width, self.input_height)
        output = self.session.run(None, {self.input_name: tensor})[0]
        detections = decode(output, scale, pad_x, pad_y, image.shape,
                            self.conf_threshold, self.iou_threshold, self.max_det)

        self.publish_detections(msg.header, image.shape, detections)
        if self.debug_pub is not None and self.debug_pub.get_subscription_count() > 0:
            self.publish_debug(msg.header, image, detections)

    def publish_detections(self, header, image_shape, detections):
        height, width = image_shape[:2]

        for x1, y1, x2, y2, confidence, class_id in detections:

            box = DetectionBoundingBox()

            box.header = header

            box.class_name = self.class_name(class_id)
            box.confidence = confidence

            box.image_width, box.image_height = width, height
            box.x_min, box.y_min = round(x1), round(y1)
            box.x_max, box.y_max = round(x2), round(y2)

            self.detections_pub.publish(box)

    def publish_debug(self, header, image, detections):

        annotated = image.copy()

        for x1, y1, x2, y2, confidence, class_id in detections:
            cv2.rectangle(annotated, (round(x1), round(y1)), (round(x2), round(y2)), DEBUG_COLOR, 2)
            cv2.putText(annotated, f'{self.class_name(class_id)} {confidence:.2f}', (round(x1), max(round(y1) - 4, 12)), cv2.FONT_HERSHEY_SIMPLEX, 0.5, DEBUG_COLOR, 2)
        
        debug_msg = self.bridge.cv2_to_imgmsg(annotated, encoding='bgr8')
        debug_msg.header = header
        self.debug_pub.publish(debug_msg)

    def class_name(self, class_id):
        return self.class_names.get(class_id, str(class_id))


def main():

    rclpy.init()
    node = YoloDetector()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.try_shutdown()


if __name__ == '__main__':
    main()
