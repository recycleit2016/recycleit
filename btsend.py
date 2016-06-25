import bluetooth

bd_addr = "90:FD:61:5F:7F:7A"
port = 1
sock = bluetooth.BluetoothSocket (bluetooth.RFCOMM)
sock.connect((bd_addr,port))

while 1:
        tosend = raw_input()
        if tosend != 'q':
                sock.send(tosend)
        else:
                break

sock.close()


