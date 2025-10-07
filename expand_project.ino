#include <Servo.h>

const int BUZZER_PIN_A = 7;
const int SERVO_PIN = 5;
float freqA;
float lastFreqA = 0;

const int TRIG_PIN_A = 9;
const int ECHO_PIN_A = 10;
float durationA, distanceA, positionA;

Servo head_servo;

void setup()
{
  pinMode(BUZZER_PIN_A, OUTPUT);
 pinMode(SERVO_PIN, OUTPUT);
  pinMode(TRIG_PIN_A, OUTPUT);
  pinMode(ECHO_PIN_A, INPUT);
  
  head_servo.attach(SERVO_PIN);
  
  Serial.begin(9600);
 
}

void loop() {  
  digitalWrite(TRIG_PIN_A, LOW);
  delayMicroseconds(2);  
  digitalWrite(TRIG_PIN_A, HIGH);  
  delayMicroseconds(10);  
  digitalWrite(TRIG_PIN_A, LOW);
 
  
  // find amount of time that it takes sound to return to sensor
  durationA = pulseIn(ECHO_PIN_A, HIGH);
 
  // use that time and the speed of sound (in ms) to calculate distance
  distanceA = (durationA * .0343)/2;
   
  Serial.print("Distance A: ");  
  Serial.println(distanceA);

  if (distanceA < 50) {
     // calculate frequency for given distance (within safe range)
    freqA = 27 + 1500 * (1 - distanceA / 50);
    positionA = 180 * (1 - distanceA / 50);
  
    // if frequency is different, change it
    if (abs(freqA - lastFreqA) > 5) {
      tone(BUZZER_PIN_A, freqA);
      lastFreqA = freqA;
    }  

    head_servo.write(positionA);
  }

  else {
    noTone(BUZZER_PIN_A);
  }
 
  delay(25);  
 

}
