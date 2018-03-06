import socket
import sys
import math

#  https://stackoverflow.com/a/18854817 
#  function to split string into fixed chunks
def chunkstring(string, length):
    return (string[0+i:length+i] for i in range(0, len(string), length))

s=socket.socket()
host= socket.gethostname()
port=12345

def send_message(sock,message_1):
    message_bits=list(chunkstring(message_1,5))
    lengthy = len(message_bits)
    for i in range(lengthy-1,-1,-1):
        message_send=packet_header+":"+str(i)+":"+str(lengthy)+":"+message_bits[i]+":"+str(lengthy)+":"+str(i)+":"+packet_header
        sock.send(message_send.encode())
    return True
    
s.bind((host,port))
packet_header="$$$"
print("Socket Opened. \nPacket header = ",packet_header)
s.listen(5)
while True:
    c,addr=s.accept()
    print("Connection request received from ",addr)
    send_message(c,"Connected to server")
    messages={}
    while True:
        check=input("Do you want to send a message (y/n) :")
        if check == "y":
            message = input("Enter message here : ")
            print(send_message(c,message))
        #print("message index = ", message_index," \nmessage content = ", messages[message_index])
 
s.close()
