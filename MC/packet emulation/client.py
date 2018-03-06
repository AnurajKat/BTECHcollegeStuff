import socket
import sys



ip=socket.gethostname()
port=12345
packet_header="$$$"
s=socket.socket()



try:
    s.connect((ip,port))
    messages={}
    while True:
        message_receive=s.recv(1024).decode()
        #print(message_receive)
        tot_message=0
        if message_receive is not None:
            print("Packet received : ",message_receive)
            parsed_message=message_receive.split(':')
            income_length= len(parsed_message)
            for i in range(0,income_length-1):
                if "$" in parsed_message[i]:
                    message_index = int(parsed_message[i+1])
                    tot_message=int(parsed_message[i+2])
                    messages[message_index]=parsed_message[i+3]
                    #print("message index = ", message_index," \nmessage content = ", messages[message_index])
                    if message_index == 0:
                        compiled_message=""
                        for i in range(0,tot_message):
                             compiled_message=compiled_message+messages[i]
                        print(compiled_message)
                        messages={}

                     
except:
    e = sys.exc_info()
    print(e)

s.close()
