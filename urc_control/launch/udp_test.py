import socket

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
    data, client_address = server_socket.recvfrom(1024)

    # Process the received data (in this example, we just print it)
    print(f"Received data from {client_address}: {data.decode('utf-8')}")

    # Optionally, send a response back to the client
    response = "Hello, client!"
    server_socket.sendto(response.encode('utf-8'), client_address)