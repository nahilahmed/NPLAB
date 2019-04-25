import socket

port = 8080
server = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
server.connect(('',port))

message = server.recv(2048)
print message

while True:
    message = raw_input()
    server.send(message)
    message = server.recv(2048)
    print message