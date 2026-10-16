Goal: Gesture Recognition for Astronaut Sub-Mission

- We must get the rover to follow--by visual feedback--an astronaut and follow as they walk to their spot, stopping within 3 meters of them (last step is task of the distance camera + state machine).
(Keep imports lazy when possible)

Current Log:
1. Both both of these in an environment on laptop cam (MPS--for YOLO) [ ]
2. Ask about imports and installs in prod environment
3. Run compute benchmarks on hardware


Current Gesture Implementations:
- Required keypoint confidence: 0.5
- Min elbow angle: 120
- Arm elevation: -10 degrees to 75
- Wrist span: 2x shoulder width




Model Choices:
1. yolo26n-pose.pt
    - Robust, can handle multiple subjects
    - But takes up more space in memory

2. movenet_lightning
    - Ultra-lightweight (on memory)
    - Only supports 1 subject, but trained on the same COCO dataset as yolo
    - tensorflow
    - not thoroughly documented on ONNX


Identification Strategy:
- The follow command will be a pose wherein the subject's arms are flared to the side and spread in a starfish-like shape.

    Relevant Keypoints:
        5. left_shoulder
        6. right_shoulder
        7. left_elbow
        8. right_elbow
        9. left_wrist
        10. right_wrist

        ~the rest are unused currently for prototype

    A follow command would be defined as: (From view of the astronaut)
        a. Where the elbows are at shoulder height, or higher, but cannot be between them, nor in-line with them vertically.
            $elbow.y <= shoulder.y + tolerance$
            $wrist.y <= elbow.y + tolerance$
        b. Where the wrists are outside of the elbows, and are higher than the elbows.
            $center_x = (left_shoulder.x + right_shoulder.x) / 2$
            $abs(elbow.x - center_x) > abs(shoulder.x - center_x)$
            $abs(wrist.x - center_x) > abs(elbow.x - center_x)$
        c. Where the angle between the forearm and the bicep is greater than 120ish degrees
            shoulder_to_elbow = shoulder - elbow
            wrist_to_elbow = wrist - elbow
            $angle = acos(dot(shoulder_to_elbow, wrist_to_elbow) / (length(shoulder_to_elbow) * length(wrist_to_elbow)))$
        d. Where the wrist-to-wrist distance is roughly 2x bigger than the width between the shoulders
            wrist_span / shoulder_width >= minimum_wingspan_ratio


HOW TO EXPORT (FROM https://docs.ultralytics.com/tasks/classify#models)

from ultralytics import YOLO

# Load a model
model = YOLO("yolo26n-pose.pt")  # load an official model
model = YOLO("path/to/best.pt")  # load a custom model

# Export the model
model.export(format="onnx")