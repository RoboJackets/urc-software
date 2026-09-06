# URC Nanopb

`urc_nanopb` provides the lightweight Protocol Buffers types used to communicate
between rover software and microcontroller firmware. It exports a library for
other ROS packages and has no runtime nodes.

## Build contract

[`proto/urc.proto`](proto/urc.proto) is the authoritative rover protocol schema.
During a workspace build, CMake uses the vendored Nanopb generator to create
`urc.pb.h` and `urc.pb.c`, compiles them into a shared library, and installs the
generated header as `urc_nanopb/urc.pb.h`.

Consumers declare a dependency on `urc_nanopb`, link its exported library, and
include the generated header:

```cpp
#include <urc_nanopb/urc.pb.h>
```

## Protocol areas

The schema includes messages for drivetrain commands and feedback, status-light
commands, battery telemetry, arm control, IMU data, and science-module control.
The drivetrain, status-light, and battery interfaces are used by `urc_hw`.

## Changing the protocol

- Update `urc.proto` and the corresponding firmware together.
- Preserve field numbers and wire compatibility; do not reuse removed field
  numbers for different data.
- Rebuild the workspace after schema changes. Generated Nanopb files are build
  outputs and should not be edited or committed.

The matching microcontroller implementation lives in the
[URC firmware repository](https://github.com/RoboJackets/urc-firmware).

