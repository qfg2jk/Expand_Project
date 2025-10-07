#include <Servo.h>

// initialize pins for buzzer and servo
const int BUZZER_PIN_A = 7;
const int SERVO_PIN = 5;

// static variables for frequency and previous frequency (used for smoothness)
float freqA;
float lastFreqA = 0;

// initialize trig and echo pin locations
const int TRIG_PIN_A = 9;
const int ECHO_PIN_A = 10;

// initialize floating point variables for sound duration, distance, and servo position
float durationA, distanceA, positionA;

Servo head_servo;

void setup()
{
  // initialize pins as i/o
  pinMode(BUZZER_PIN_A, OUTPUT);
  pinMode(SERVO_PIN, OUTPUT);
  pinMode(TRIG_PIN_A, OUTPUT);
  pinMode(ECHO_PIN_A, INPUT);
  
  head_servo.attach(SERVO_PIN);
  
  Serial.begin(9600);
 
}

void loop() {  
  // broadcast ultrasonic sound (code used from https://projecthub.arduino.cc/Isaac100/getting-started-with-the-hc-sr04-ultrasonic-sensor-7cabe1)
  digitalWrite(TRIG_PIN_A, LOW);
  delayMicroseconds(2);  
  digitalWrite(TRIG_PIN_A, HIGH);  
  delayMicroseconds(10);  
  digitalWrite(TRIG_PIN_A, LOW);
 
  
  // find amount of time that it takes sound to return to sensor
  durationA = pulseIn(ECHO_PIN_A, HIGH);
 
  // use that time and the speed of sound (in ms) to calculate distance
  distanceA = (durationA * .0343)/2;
  
  // print out distance to command line
  Serial.print("Distance A: ");  
  Serial.println(distanceA);

  // only distances within 50cm of the sensor will output sound
  if (distanceA < 50) {
     // calculate frequency and servo position for given distance (within safe range)
    freqA = 27 + 1500 * (1 - distanceA / 50);
    positionA = 180 * (1 - distanceA / 50);
  
    // if frequency is different, change it
    if (abs(freqA - lastFreqA) > 5) {
      tone(BUZZER_PIN_A, freqA);
      lastFreqA = freqA;
    }  

    // adjust servo position
    head_servo.write(positionA);
  }

  // if not within range, make no noise
  else {
    noTone(BUZZER_PIN_A);
  }

  delay(25);  
 

}
