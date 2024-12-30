// Opdracht 7 - Ultrasonic distance controlling the servo within certain limits
// Written by: Nina Schrauwen
#include <Servo.h>
// Define constant variables
const int TRIG = 12;
const int ECHO = 13;
const int SERVO = 2;
// Define global variables
long duration;
int distance;
int angle;

Servo servo; // Make a Servo object

void setup()
{
  // Start serial communication
  Serial.begin(9600);
  // // Set up ultrasonic sensor pins as input and output
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  
  servo.attach(SERVO);
  
  servo.write(0);  // Resting position has to be 0 degrees
}

void loop()
{
  // Make sure the pulse is clean by making sure the trigger was off before using it
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  // Send a short pulse to initiate measurement
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  
  // Measure the duration of the echo signal
  duration = pulseIn(ECHO, HIGH);
  
  // Measure the distance in cm
  distance = duration * 0.0344 /2;
  
  // Debug print to double check the distance
  Serial.print("Afstand: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  // If the measured distance (in cm) is between 4 and 10
  if(distance >= 4 && distance <= 10){
    // Map the distance range (4-10 cm) to a servo angle (90-180 degrees)
    angle = map(distance, 4, 10, 90, 180);
    servo.write(angle);
    Serial.print(angle);
    Serial.println(" graden");
  } else {
    // Otherwise back to resting position
    servo.write(0);
  }
  
  delay(500); // Delay for stability 
  
}
