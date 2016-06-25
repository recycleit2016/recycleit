#define trigPin1 8
#define echoPin1 7
#define trigPin2 12
#define echoPin2 11
#define trigPin3 4
#define echoPin3 3

#define LEDPin1 13 // Onboard LED blue
#define LEDPin2 6 // Onboard LED red
#define LEDPin3 5 // Onboard LED grin


//GPIO PORT IN
#define LEDPin1 9 // Red
#define LEDPin2 10 // Green
#define LEDPin3 2 // Blue

#define TESTPIN 1 //TEST PIN

int maximumRange = 25; // Maximum range needed
int minimumRange = 0; // Minimum range needed 
long duration, duration2, distance, distance2, BlueSensor,RedSensor,GrinSensor;

int gFlag=1;
int flag1=0, flag2=0, flag3=0;
int lflag=1; //int lflag1=1, lflag2=1, lflag3=1;

void setup()
{
	//Serial.begin (9600);
	pinMode(trigPin1, OUTPUT);
	pinMode(echoPin1, INPUT);
	pinMode(trigPin2, OUTPUT);
	pinMode(echoPin2, INPUT);
	pinMode(trigPin3, OUTPUT);
	pinMode(echoPin3, INPUT);

	pinMode(LEDPin1, OUTPUT);
	pinMode(LEDPin2, OUTPUT);
	pinMode(LEDPin3, OUTPUT);

	pinMode(PININ1, INPUT);
	pinMode(PININ2, INPUT);
	pinMode(PININ3, INPUT);
	
	pinMode(PINOUT1, OUTPUT);
	
	pinMode(PINOUT1, HIGH);
}

void loop() {
	if (gFlag) {
		gFlag = 0;
		if (PININ1 == 1 && PININ2 == 0 && PININ3 == 0) {
			flag1=1;
		} else if (PININ1 == 0 && PININ2 == 1 && PININ3 == 0) {
			flag2=1;
		} else if (PININ1 == 0 && PININ2 == 0 && PININ3 == 1) {
			flag3=1;
		}
	}
	
	if (flag1 == 1) {
		SonarSensor(trigPin1, echoPin1);
		if (!lflag) {
			digitalWrite(LEDPin1, LOW); 
			flag1 = 0;
		}
		BlueSensor = distance;
	} else if (flag2 == 1) {
		SonarSensor(trigPin2, echoPin2);
		if (!lflag) {
			digitalWrite(LEDPin2, LOW);
			flag2 = 0;
		}
		RedSensor = distance2;
	} else if (flag3 == 1) {
		SonarSensor(trigPin3, echoPin3);
		if (!lflag) {
			digitalWrite(LEDPin3, LOW);
			flag3 = 0;
		}
		GrinSensor = distance;
	}
	gFlag = 1;
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

   if (!(distance >= maximumRange || distance <= minimumRange)){
		/* Send the distance to the computer using Serial protocol, and
		turn LED ON to indicate successful reading. */
		
		lflag = 0;
     }
 
    //Delay 50ms before next reading.
    delay(100);
}



