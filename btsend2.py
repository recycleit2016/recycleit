import bluetooth

bd_addr = "98:4F:EE:0F:76:BE"
port = 1

sock=bluetooth.BluetoothSocket( bluetooth.RFCOMM )
sock.connect((bd_addr, port))

sock.send("hello!!")
sock.close()
