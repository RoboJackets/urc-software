# URC Util

This package is a collection of helpful classes and headers that help in various other packages in the repo.

- ### Ethernet Socket
  - Utility wrapper class for the boost::ip::udp library
  - Makes UDP communication over ethernet easier to implement
  - Mainly in use in [urc_platform](../urc_platform/) for firmware communications


- ### Probability Utils
  - Header-only library for going to and from log odds, type-agnostic design
  - Mainly in use in [urc_nav2_plugins](../urc_nav2_plugins/) for calculating the probability of a costmap grid space
    being clear/occupied