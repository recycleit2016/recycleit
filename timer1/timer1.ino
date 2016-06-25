#include <TimerOne.h>

/*
 *  Timer1 library example
 *  June 2008 | jesse dot tane at gmail dot com
 */
int trigger;

void setup()
{
  trigger = 0;
  pinMode(13, OUTPUT);
  Timer1.initialize(2000000);         // initialize timer1, and set a 1/2 second period
  Timer1.attachInterrupt(callback);  // attaches callback() as a timer overflow interrupt
}
 
void callback()
{
  if (trigger==0)
    digitalWrite(13, HIGH);
  else
    digitalWrite(13, LOW);
  trigger=~trigger;
}
 
void loop()
{
  ;// your program here...;
}
