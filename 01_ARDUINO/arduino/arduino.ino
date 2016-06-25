#define trigPin1 8
#define echoPin1 7
#define trigPin2 12
#define echoPin2 11
#define trigPin3 4
#define echoPin3 3

#define LEDPin1 13 // Onboard LED blue
#define LEDPin2 6 // Onboard LED red
#define LEDPin3 5 // Onboard LED grin

int maximumRange = 200; // Maximum range needed
int minimumRange = 0; // Minimum range needed 
long duration, distance, BlueSensor,RedSensor,GrinSensor;

void setup()
{
Serial.begin (9600);
pinMode(trigPin1, OUTPUT);
pinMode(echoPin1, INPUT);
pinMode(trigPin2, OUTPUT);
pinMode(echoPin2, INPUT);
pinMode(trigPin3, OUTPUT);
pinMode(echoPin3, INPUT);

pinMode(LEDPin1, OUTPUT);
pinMode(LEDPin2, OUTPUT);
pinMode(LEDPin3, OUTPUT);
}

void loop() {
SonarSensor(trigPin1, echoPin1);
BlueSensor = distance;
SonarSensor(trigPin2, echoPin2);
RedSensor = distance;
SonarSensor(trigPin3, echoPin3);
GrinSensor = distance;
Serial.println(BlueSensor);
Serial.println(RedSensor);
Serial.println(GrinSensor);
}

void SonarSensor(int trigPin,int echoPin)
{
digitalWrite(trigPin, LOW);
delayMicroseconds(2); 
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance = (duration/2) / 29.1;

if (distance >= maximumRange || distance <= minimumRange){
 /* Send a negative number to computer and Turn LED OFF 
 to indicate "out of range" */
  Serial.println("-1");
  digitalWrite(LEDPin1, LOW);
  digitalWrite(LEDPin2, LOW);
  digitalWrite(LEDPin3, LOW); 
 }

 else{
 /* Send the distance to the computer using Serial protocol, and
 turn LED ON to indicate successful reading. */
  Serial.println(distance);
  Serial.println(BlueSensor);
  Serial.println(RedSensor);
  Serial.println(GrinSensor);
  
  digitalWrite(LEDPin1, HIGH); 
  digitalWrite(LEDPin2, HIGH);
  digitalWrite(LEDPin3, HIGH);
 }
 
 //Delay 50ms before next reading.
 delay(100);
}

