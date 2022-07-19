## URC Nanopb

[Nanopb](https://github.com/nanopb/nanopb) is a Protocol Buffers implementation designed to efficiently package/encapsulate messages for communication with the [urc_firmware stack](https://github.com/RoboJackets/urc-firmware). It is a submodule of this repo, and the .proto messages it will use are defined in the /proto directory of this package.


This package...
1. Uses nanopb to convert the .proto files into cpp/hpp files
2. Creates a library with those files and any other necessary nanopb files
3. Makes all those files accessible in the `urc_nanopb` package


