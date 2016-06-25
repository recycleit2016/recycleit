char blueToothVal;           //value sent over via bluetooth
char lastValue;              //stores last state of device (on/off)
 
const int ledPin0 = 12; // pin to use for the LED bin 0
const int ledPin1 = 11; // pin to use for the LED bin 1
const int ledPin2 = 10; // pin to use for the LED bin 2

void setup()
{
 Serial.begin(9600); 
 pinMode(ledPin0, OUTPUT);
 pinMode(ledPin1, OUTPUT);
 pinMode(ledPin2, OUTPUT);
}
 
void loop()
{
  if(Serial.available()){
                                //if there is data being recieved
    blueToothVal=Serial.read(); //read it
  
    if (blueToothVal==1)
    {                 // Logic for Bin 0; Item 1
      digitalWrite(ledPin0, HIGH);
      
      if (lastValue!=1)
        Serial.println(F("Bin 0; Item 2")); //print LED is on
      lastValue=blueToothVal;
    }
  
    else {
      Serial.println(F("No data")); //print LED is on
      digitalWrite(ledPin0, LOW);
      digitalWrite(ledPin1, LOW);
      digitalWrite(ledPin2, LOW);
    }
  }

  delay(1000);
}
