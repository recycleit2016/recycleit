
 
#define echoPin 7 // Echo Pin
#define echoPin_r 11 // Echo Pin red
#define trigPin 8 // Trigger Pin
#define trigPin_r 12 // Trigger Pin red
#define LEDPin 13 // Onboard LED
#define LEDPin_r 6 // Onboard LED red
 
int maximumRange = 200; // Maximum range needed
int minimumRange = 0; // Minimum range needed   
long duration, duration_r,  distance , distance_r ; // Duration used to calculate distance
 
void setup() {
 Serial.begin (9600);
 pinMode(trigPin, OUTPUT);
 pinMode(trigPin_r, OUTPUT);
 pinMode(echoPin, INPUT);
 pinMode(echoPin_r, INPUT);
 pinMode(LEDPin, OUTPUT); // Use LED indicator 
 pinMode(LEDPin_r, OUTPUT); 
}
 
void loop() {
/* The following trigPin/echoPin cycle is used to determine the
 distance of the nearest object by bouncing soundwaves off of it. */ 
 digitalWrite(trigPin, LOW);
 digitalWrite(trigPin_r, HIGH); 
 delayMicroseconds(2); 
 
 digitalWrite(trigPin, HIGH);
 digitalWrite(trigPin_r, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(trigPin, LOW);
 digitalWrite(trigPin_r, LOW);
 duration = pulseIn(echoPin, HIGH);
 duration_r = pulseIn(echoPin_r, HIGH);
 
 //Calculate the distance (in cm) based on the speed of sound.
 distance = duration/58.2;
 distance_r = duration_r/58.2;
 
 if (distance >= maximumRange || distance <= minimumRange){
 /* Send a negative number to computer and Turn LED OFF 
 to indicate "out of range" */
  Serial.println("-1");
  digitalWrite(LEDPin, LOW); 
 }
 else if(distance >= maximumRange || distance <= minimumRange){
  Serial.println("-1");
  digitalWrite(LEDPin_r, LOW);
 }
 else{
 /* Send the distance to the computer using Serial protocol, and
 turn LED ON to indicate successful reading. */
  Serial.println(distance);
  Serial.println(distance_r);
  digitalWrite(LEDPin, HIGH);
  digitalWrite(LEDPin_r, HIGH);
 }
 
 //Delay 10ms before next reading.
 delay(10);
}
