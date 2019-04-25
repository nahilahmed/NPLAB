import socket
import threading

port = 8080
server = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
server.bind(('',port))
server.listen(100)

listc = []

def clientthread (conn , addr):
    conn.send("Hi from Server")
    while True:
        message = conn.recv(2048)
        message = "User" + str(addr) + message
        print message
        for connection in listc:
            if(connection!=conn):
                connection.send(message)
         


while True:
    conn , addr = server.accept()
    listc.append(conn)
    print addr[0]+" Connected"
    t = threading.Thread(target=clientthread,args=(conn,addr))
    t.start()
