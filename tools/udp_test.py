import socket
import urc_pb2
import google.protobuf as pb


# Define the server's IP address and port
server_ip = "127.0.0.1"  # Replace with your server's IP address
server_port = 5000  # Replace with the desired port number

# Create a UDP socket
server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Bind the socket to the server's address and port
server_socket.bind((server_ip, server_port))

print(f"UDP server is listening on {server_ip}:{server_port}")

while True:
    # Receive data from a client
    data, client_address = server_socket.recvfrom(128)

    msg = urc_pb2.DriveEncodersMessage()
    msg.ParseFromString(data)

    print(msg.leftSpeed)
