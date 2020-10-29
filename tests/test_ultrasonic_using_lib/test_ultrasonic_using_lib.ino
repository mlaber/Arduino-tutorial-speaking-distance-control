/* Example code for HC-SR04 ultrasonic distance sensor with Arduino.Using HCSR04 library.  */



// system libraries
#include "Arduino.h"
#include "HCSR04.h"


int triggerPin = 5;    // utrasonic-senor trigger pin
int echoPin = 18;        // utrasonic-senor echo pin

// Define variables:
long duration;
int distance;

void setup() {
  // Define inputs and outputs:
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //Begin Serial communication at a baudrate of 115200:
  Serial.begin(115200);

  UltraSonicDistanceSensor distanceSensor(triggerPin, echoPin);
}

void loop() {
  double distance1 = distanceSensor.measureDistanceCm();
    Serial.print("Distance to object (cm) ");Serial.println(distance1);
  delay(50);
}
