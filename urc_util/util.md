# urc_util

## Overview

The `urc_util` package provides utility functionality for URC rover projects, including networking, messaging, and helper functions.

This system includes the following modules:

1. **EthernetSocket**  
   - Provides UDP socket communication using Boost.Asio.  
   - Supports sending and receiving messages over Ethernet, retrieving remote endpoint information, and versioning of Boost.

---

## Features

- **UDP Communication**: Simple interface for sending and receiving messages via UDP.  
- **Endpoint Management**: Automatically resolves IP addresses and ports, including broadcast communication.  
- **Boost Version Info**: Utility function to get the Boost library version used.  
- **Exception Handling**: Proper handling of network errors and connection shutdown.

---

## Package Structure

```
├── CMakeLists.txt
├── include
│   └── urc_util
│       └── ethernet_socket.hpp
├── launch
├── package.xml
└── src
    └── ethernet_socket.cpp

```

---

### EthernetSocket

- **EthernetSocket (`ethernet_socket.hpp/cpp`)**
  - Provides a class for creating and managing UDP sockets using Boost.Asio.
  - Supports both server-style (bind to port) and client-style (connect to remote IP/port) sockets.
  - Key functionalities:
    - **sendMessage(char*, size_t)**: Broadcast or send messages to a remote endpoint.
    - **readMessage(unsigned char(&)[256])**: Receive messages from the socket with error handling.
    - **getIP()**: Retrieve the IP address of the remote endpoint.
    - **getPort()**: Retrieve the port of the remote endpoint.
    - **getBoostVersion()**: Returns the Boost library version as a string.
  - Properly shuts down the socket on destruction.


