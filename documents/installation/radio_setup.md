# Ubiquiti Bullet (Radio) Setup Guide
Connect the antenna to the Ubiquiti bullet. Plug in the PoE injector, and connect the PoE port to the bullet and the LAN port to your computer.
## For Native OS
 1. In network settings, configure your ethernet adapter to have a static IPv4 address of with a subnet mask `255.255.255.0`.
 3. Log in with username `ubnt` and password `access`.
 4. If you are configuring a non-access point, open https://192.168.1.20 in a browser. Log in with username `ubnt` and password `station`.

## For Ubuntu VMs:

 1. Create a new network adapter for the VM in VirtualBox, and set it to a bridged connection. Initially, set the bridge to `en0: Wi-Fi`, otherwise the VM will not start.
 2. Once the VM has started, set the bridge to `en5: USB Ethernet`. This may be different based on your host OS.
 3. Follow the steps for Native OS on your VM.

# Overview of Radio Network
![network diagram](../pictures/network.png)
