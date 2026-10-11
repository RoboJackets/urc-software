import time
from pathlib import Path

import cv2
import numpy as np
import rclpy
from rcl_interfaces.msg import ParameterDescriptor
from rclpy.node import Node
from rclpy.qos import HistoryPolicy, QoSProfile, ReliabilityPolicy
from sensor_msgs.msg import Image
from vision_msgs.msg import Detection2D, Detection2DArray, ObjectHypothesisWithPose
from ultralytics import YOLO

def image_to_bgr(msg: Image) -> np.ndarray:

    enc = msg.encoding.lower()
    channels = {"bgr8": 3, "rgb8": 3, "bgra8": 4, "rgba8": 4, "mono8": 1}.get(enc)

    if channels is None:
        from cv_bridge import CvBridge 
        return CvBridge().imgmsg_to_cv2(msg, "bgr8")

    buf = np.frombuffer(msg.data, dtype=np.uint8)
    img = buf.reshape(msg.height, msg.step)[:, : msg.width * channels]
    img = img.reshape(msg.height, msg.width, channels)

    if enc == "rgb8":
        return cv2.cvtColor(img, cv2.COLOR_RGB2BGR)
    if enc == "bgra8":
        return cv2.cvtColor(img, cv2.COLOR_BGRA2BGR)
    if enc == "rgba8":
        return cv2.cvtColor(img, cv2.COLOR_RGBA2BGR)
    if enc == "mono8":
        return cv2.cvtColor(img, cv2.COLOR_GRAY2BGR)

    return img.copy()


def bgr_to_image(img: np.ndarray, header) -> Image:
    msg = Image()
    msg.header = header
    msg.height, msg.width = img.shape[:2]
    msg.encoding = "bgr8"
    msg.is_bigendian = 0
    msg.step = msg.width * 3
    msg.data = np.ascontiguousarray(img).tobytes()
    return msg


class YoloDetectorNode(Node):
    def __init__(self):

        super().__init__("yolo_detector")
    
        loose = ParameterDescriptor(dynamic_typing=True)
        p = lambda name, default: self.declare_parameter(name, default, loose)  
        self.model_path = str(p("model", "").value)

        if not self.model_path:
            raise SystemExit("yolo_detector model not found")

        if not Path(self.model_path).is_file():
            raise SystemExit(f"yolo_detector: model file not found: {self.model_path}")

        self.image_topic = p("image_topic", "/camera/image_raw").value
        self.det_topic = p("detections_topic", "/yolo/detections").value
        self.ann_topic = p("annotated_topic", "/yolo/annotated").value

        self.publish_annotated = str(p("publish_annotated", True).value).lower() in ("true", "1")

        self.conf = float(p("confidence_threshold", 0.40).value)
        self.iou = float(p("iou_threshold", 0.45).value)
        self.imgsz = int(p("image_size", 640).value)
        self.max_det = int(p("max_detections", 50).value)
        self.device = str(p("device", "0").value)      

        self.half = str(p("half", True).value).lower() in ("true", "1")  

        self.get_logger().info(f"Loading model {self.model_path} ...")
        self.model = YOLO(self.model_path, task="detect")

        self.names = self.model.names                  
        
        self.model.predict(np.zeros((self.imgsz, self.imgsz, 3), np.uint8), imgsz=self.imgsz, device=self.device, verbose=False, half=self.half)
        self.get_logger().info(f"Classes: {self.names}")

        sensor_qos = QoSProfile(reliability=ReliabilityPolicy.BEST_EFFORT, history=HistoryPolicy.KEEP_LAST, depth=1)
        self.sub = self.create_subscription(Image, self.image_topic, self.on_image, sensor_qos)
        self.det_pub = self.create_publisher(Detection2DArray, self.det_topic, 10)
        self.ann_pub = (self.create_publisher(Image, self.ann_topic, 1) if self.publish_annotated else None)

        self.frames, self.t0 = 0, time.time()
        self.get_logger().info(f"Listening on {self.image_topic}, publishing {self.det_topic}")

    def on_image(self, msg: Image):
        try:
            frame = image_to_bgr(msg)
        except Exception as e: 
            self.get_logger().error(f"Image conversion failed ({msg.encoding}): {e}", throttle_duration_sec=5.0)
            return

        result = self.model.predict(frame, conf=self.conf, iou=self.iou, imgsz=self.imgsz, max_det=self.max_det, device=self.device, half=self.half, verbose=False)[0]

        out = Detection2DArray()
        out.header = msg.header
        boxes = result.boxes

        for (x1, y1, x2, y2), score, cls in zip(boxes.xyxy.tolist(), boxes.conf.tolist(), boxes.cls.tolist()):
            det = Detection2D()
            det.header = msg.header
            det.bbox.center.position.x = (x1 + x2) / 2.0
            det.bbox.center.position.y = (y1 + y2) / 2.0
            det.bbox.center.theta = 0.0
            det.bbox.size_x = x2 - x1
            det.bbox.size_y = y2 - y1
            hyp = ObjectHypothesisWithPose()
            hyp.hypothesis.class_id = self.names[int(cls)]
            hyp.hypothesis.score = float(score)
            det.results.append(hyp)
            out.detections.append(det)

        self.det_pub.publish(out)

        if self.ann_pub is not None and self.ann_pub.get_subscription_count() > 0:
            self.ann_pub.publish(bgr_to_image(result.plot(), msg.header))

        self.frames += 1

        if time.time() - self.t0 >= 5.0:
            fps = self.frames / (time.time() - self.t0)
            summary = ", ".join(f"{d.results[0].hypothesis.class_id} "f"{d.results[0].hypothesis.score:.2f}" for d in out.detections)
            
            self.get_logger().info(f"{fps:.1f} FPS | last frame: {summary or 'nothing'}")
            self.frames, self.t0 = 0, time.time()


def main():
    rclpy.init()
    node = None

    try:
        node = YoloDetectorNode()
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass

    except SystemExit as e:
        print(e, flush=True)

    finally:
        if node is not None:
            node.destroy_node()
        rclpy.try_shutdown()


if __name__ == "__main__":
    main()