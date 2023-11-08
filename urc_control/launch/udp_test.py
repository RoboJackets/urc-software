import socket
import urc_pb2
import google.protobuf as pb


# Define the server's IP address and port
server_ip = "192.168.1.168"  # Replace with your server's IP address
server_port = 8443  # Replace with the desired port number

# Create a UDP socket
server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Bind the socket to the server's address and port
server_socket.bind((server_ip, server_port))

print(f"UDP server is listening on {server_ip}:{server_port}")

while True:
    # Receive data from a client
    data, client_address = server_socket.recvfrom(1024)

    msg = urc_pb2.StatusLightCommand()
    msg.ParseFromString(data)
    print(msg.color, "  ", msg.display)
