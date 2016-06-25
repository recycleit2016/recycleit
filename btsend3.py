#! /usr/bin/python

import serial
from time import sleep

bluetoothSerial = serial.Serial( "/dev/serial1", baudrate=9600 )

count = None
while count == None:
    try:
        count = int(raw_input( "Please"))
    except:
        pass    # Ignore any errors that may occur and try again

print count
bluetoothSerial.write( str(count) )
print bluetoothSerial.readline()
