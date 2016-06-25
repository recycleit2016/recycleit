/*
   Copyright (c) 2015 Intel Corporation.  All rights reserved.

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include <CurieBLE.h>

BLEPeripheral blePeripheral;  // BLE Peripheral Device (the board you're programming)
BLEService ledService("19B10000-E8F2-537E-4F6C-D104768A1214"); // BLE LED Service

// BLE LED Switch Characteristic - custom 128-bit UUID, read and writable by central
BLEUnsignedCharCharacteristic switchCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);

int blueToothVal;           //value sent over via bluetooth

const int Item01 = 1;  // Item 01
const int Item02 = 2;  // Item 02
const int Item03 = 3;  // Item 03
const int Item04 = 4;  // Item 04
const int Item05 = 5;  // Item 05
const int Item06 = 6;  // Item 06
const int Item07 = 7;  // Item 07
const int Item08 = 8;  // Item 08
const int Item09 = 9;  // Item 09
const int Item10 = 10;  // Item 10
const int Item11 = 11;  // Item 11
const int Item12 = 12;  // Item 12
 
const int ledPin0 = 12; // pin to use for the LED bin 0
const int ledPin1 = 11; // pin to use for the LED bin 1
const int ledPin2 = 10; // pin to use for the LED bin 2

void setup() {
  Serial.begin(9600);

  // set LED pin to output mode
 pinMode(ledPin0, OUTPUT);
 pinMode(ledPin1, OUTPUT);
 pinMode(ledPin2, OUTPUT);

  // set advertised local name and service UUID:
  blePeripheral.setLocalName("testLED");
  blePeripheral.setAdvertisedServiceUuid(ledService.uuid());

  // add service and characteristic:
  blePeripheral.addAttribute(ledService);
  blePeripheral.addAttribute(switchCharacteristic);

  // set the initial value for the characeristic:
  switchCharacteristic.setValue(0);

  // begin advertising BLE service:
  blePeripheral.begin();

  Serial.println("BLE LED Peripheral");
}

void loop() {
  // listen for BLE peripherals to connect:
  BLECentral central = blePeripheral.central();

  // if a central is connected to peripheral:
  if (central) {
    Serial.print("Connected to central: ");
    // print the central's MAC address:
    Serial.println(central.address());

    // while the central is still connected to peripheral:
    while (central.connected()) {
      // if the remote device wrote to the characteristic,
      // use the value to control the LED:
      
      if (switchCharacteristic.written()) {
        //if (switchCharacteristic.value()) {   // any value other than 0
        //  Serial.println("LED on");
        //  digitalWrite(ledPin, HIGH);         // will turn the LED on
        //} else {                              // a 0 value
        //  Serial.println(F("LED off"));
        //  digitalWrite(ledPin, LOW);          // will turn the LED off
        //}
                
          if (switchCharacteristic.value()) {
            blueToothVal=switchCharacteristic.value();

            if (blueToothVal==Item01){
              digitalWrite(ledPin0, HIGH);
              Serial.println(F("Bin 0; Item 1")); //print LED is on 
              
            }
            else if (blueToothVal==Item02) {
              digitalWrite(ledPin0, HIGH);
              Serial.println(F("Bin 0; Item 2")); //print LED is on 
              
            }
            else if (blueToothVal==Item03) {
              digitalWrite(ledPin0, HIGH);
              Serial.println(F("Bin 0; Item 3")); //print LED is on 
              
            }
            else if (blueToothVal==Item04) {
              digitalWrite(ledPin0, HIGH);
              Serial.println(F("Bin 0; Item 4")); //print LED is on 
              
            }
            else if (blueToothVal==Item05) {
              digitalWrite(ledPin1, HIGH);
              Serial.println(F("Bin 1; Item 5")); //print LED is on 
              
            }
            else if (blueToothVal==Item06) {
              digitalWrite(ledPin1, HIGH);
              Serial.println(F("Bin 1; Item 6")); //print LED is on 
              
            }
            else if (blueToothVal==Item07) {
              digitalWrite(ledPin1, HIGH);
              Serial.println(F("Bin 1; Item 7")); //print LED is on 
              
            }
            else if (blueToothVal==Item08) {
              digitalWrite(ledPin1, HIGH);
              Serial.println(F("Bin 1; Item 8")); //print LED is on 
              
            }
            else if (blueToothVal==Item09) {
              digitalWrite(ledPin2, HIGH);
              Serial.println(F("Bin 2; Item 9")); //print LED is on 
              
            }
            else if (blueToothVal==Item10) {
              digitalWrite(ledPin2, HIGH);
              Serial.println(F("Bin 2; Item 10")); //print LED is on 
              
            }
            else if (blueToothVal==Item11) {
              digitalWrite(ledPin2, HIGH);
              Serial.println(F("Bin 2; Item 11")); //print LED is on 
              
            }
            else if (blueToothVal==Item12) {
              digitalWrite(ledPin2, HIGH);
              Serial.println(F("Bin 2; Item 12")); //print LED is on 
              
            }
          }
  
          else {
            digitalWrite(ledPin0, LOW);
            digitalWrite(ledPin1, LOW);
            digitalWrite(ledPin2, LOW);   
          }
        } 
      }
    }

    // when the central disconnects, print it out:
    Serial.print(F("Disconnected from central: "));
    Serial.println(central.address());
  
}

