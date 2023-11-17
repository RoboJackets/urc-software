
# Import socket module
import socket

# Create a UDP socket
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Define the server address and port
server_address = ('192.168.1.168', 8443)

# Send a message to the server
message = b'Hello, this is a UDP message'
sock.sendto(message, server_address)

# Receive a response from the server
data, address = sock.recvfrom(4096)
print(f'Received {data} from {address}')

# Close the socket
sock.close()
