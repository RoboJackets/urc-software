#!/usr/bin/env python
from sensor_msgs.msg import Image as ImMsg
from sensor_msgs.msg import CompressedImage
from sensor_msgs.msg import CameraInfo
from cv_bridge import CvBridge
import rclpy
import cv2
import functools
import numpy as np
import sys
from timeit import default_timer as timer
import torch
from torch.autograd import Variable
import segmentation_models_pytorch as smp

import os
sys.path.append(os.path.dirname(os.path.abspath(__file__)) + "/../")


class SegmentationModel(object):
    
    # Segmentation for line detection

    def __init__(
            self,
            camera_names,
            publisher_topic,
            **kwargs):

        self.bridge = CvBridge()

        self.force_cpu = kwargs["force_cpu"]
        self.encoder = kwargs["encoder"]
        self.encoder_weights = kwargs["encoder_weights"]
        self.resize_width = kwargs["resize_width"]
        self.resize_height = kwargs["resize_height"]

        # Set up U-Net with EfficientNet backbone pretrained on ImageNet
        if self.force_cpu:
            DEVICE = 'cpu'
        else:
            DEVICE = 'cuda'
        ACTIVATION = None

        self.model = smp.Unet(
            encoder_name=self.encoder,
            encoder_weights=self.encoder_weights,
            classes=3,
            activation=ACTIVATION,
        )

        # Load weights from file
        bestModel = torch.load(
            kwargs["model_filename"],
            map_location=torch.device(DEVICE)
        )
        self.model.load_state_dict(bestModel['model_state_dict'])

        if torch.cuda.is_available() and not self.force_cpu:
            self.model.cuda()
        elif ((torch.cuda.is_available() is False) and self.force_cpu):
            rclpy.logerr(f"Conflict with device and cuda! Device: {DEVICE}, \
                CUDA: {torch.cuda.is_available()}"
                         )
            sys.exit()

        self.model.eval()

        # Setup publisher and subscriber for each camera.
        self.subscribers = []
        self.im_publishers = {}

        for camera_name in camera_names:
            rclpy.loginfo(f"Setting up {camera_name}.")
            try:
                cam_info_topic = os.path.join(camera_name, "/raw/camera_info")
                camera_info = rclpy.wait_for_message(
                    cam_info_topic,
                    CameraInfo,
                    timeout=5
                )
            except rclpy.ROSException:
                rclpy.logerr(f"Camera info for {camera_name} not available.")
                sys.exit()
            rclpy.loginfo(camera_info)

            # Create image publishers.
            cam_img_topic = os.path.join(camera_name, publisher_topic)
            self.im_publishers[camera_name] = rclpy.Publisher(
                cam_img_topic,
                ImMsg,
                queue_size=1
            )

            print(f"Finished setting up {camera_name}.")

        for camera_name in camera_names:
            # Use the same callback for every camera.
            cam_img_topic = os.path.join(camera_name, "raw/image/compressed")
            self.subscribers.append(
                rclpy.Subscriber(cam_img_topic,
                                 CompressedImage,
                                 functools.partial(self.image_cb, camera_name),
                                 queue_size=1,
                                 buff_size=10**8
                                 )
            )

        rclpy.loginfo('Line detector is running.')

    def image_cb(self, camera_name, data):
        # Track inference time.
        start = timer()

        # Convert Buffer to Image
        np_arr = np.frombuffer(data.data, np.uint8)
        image_np = cv2.imdecode(np_arr, cv2.IMREAD_COLOR)

        # Resize image
        image_np = cv2.resize(
            image_np,
            dsize=(self.resize_width, self.resize_height)
        )

        # Swap dimensions around to the dimensions the model expects
        image_np = np.swapaxes(image_np, 2, 0)
        image_np = np.swapaxes(image_np, 2, 1)

        # Convert to tensor
        img_to_tensor = torch.from_numpy(image_np).float()

        if not self.force_cpu:
            img_to_tensor = Variable(img_to_tensor.unsqueeze(0)).cuda()
        else:
            img_to_tensor = Variable(img_to_tensor.unsqueeze(0))
        output = self.model(img_to_tensor)
        pred_mask = output.cpu().data.numpy()[0]

        # Convert back to image dimensions
        pred_mask = np.swapaxes(pred_mask, 2, 0)
        pred_mask = np.swapaxes(pred_mask, 1, 0)

        # Take most likely prediction
        pred_mask = np.argmax(pred_mask, axis=2)

        # Network output values above threshold are lines.
        colorImg = cv2.cvtColor(
            pred_mask.astype(np.uint8),
            cv2.COLOR_GRAY2BGR
        )

        # Multiclass Segmentation Visualization
        # lineMask = np.all(colorImg == [2, 2, 2], axis=2)
        # colorImg[lineMask] = [255, 255, 255]
        # barrelMask = np.all(colorImg == [1, 1, 1], axis=2)
        # colorImg[barrelMask] = [0, 255, 0]
        # msg_out = self.bridge.cv2_to_imgmsg(colorImg, 'bgr8')
        # msg_out.header.stamp = data.header.stamp
        # self.im_publishers[camera_name].publish(msg_out)

        # Producing Binary Mask for lines
        lineMask = np.all(colorImg == [2, 2, 2], axis=2)
        colorImg[lineMask] = [255, 255, 255]
        colorImg[~lineMask] = [0, 0, 0]
        msg_out = self.bridge.cv2_to_imgmsg(colorImg, 'bgr8')
        msg_out.header.stamp = data.header.stamp
        self.im_publishers[camera_name].publish(msg_out)

        end = timer()
        rclpy.loginfo(f"inference time: {end - start}")


if __name__ == '__main__':
    node = rclpy.Node('multiclass_segmentation')

    # Read params.
    camera_names = node.get_parameter('camera_names')
    segmentation_topic = node.get_parameter('segmentation_topic')

    model_path = node.get_parameter('model_path')
    force_cpu = node.get_parameter('force_cpu')
    encoder = node.get_parameter('encoder', 'efficientnet-b3')
    encoder_weights = node.get_parameter('encoder_weights', 'imagenet')

    image_resize_width = node.get_parameter('image_resize_width')
    image_resize_height = node.get_parameter('image_resize_height')

    SegmentationModel(camera_names,
                      segmentation_topic,
                      model_filename=model_path,
                      force_cpu=force_cpu,
                      encoder=encoder,
                      encoder_weights=encoder_weights,
                      resize_width=image_resize_width,
                      resize_height=image_resize_height
                      )

    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        node.get_logger().error("Shutting down")
        node.destroy_node()
        rclpy.shutdown()
