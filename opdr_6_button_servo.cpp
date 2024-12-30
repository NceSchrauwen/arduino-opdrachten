// Opdracht 6 - Servo rotate from 0 to 120 degrees with differing speeds
// Written by: Nina Schrauwen 
#include <Servo.h> 

Servo myServo; // Create a servo object
// Define constant variables
const int BTN1 = 3;
const int BTN2 = 4;
const int SERVO = 2;

// Define states
enum Mode {
  IDLE,
  BTN1_MODE,
  BTN2_MODE,
  BOTH_BTNS_MODE
};

// Define global variables
Mode currentMode = IDLE; // Start in IDLE mode 
int btnState1 = 0;
int btnState2 = 0;
int angle;
int steps;
int delayTime;

void setup()
{
  // Start serial communication
  Serial.begin(9600);
  // Define inputs with pins
  pinMode(BTN1, INPUT_PULLUP);
  pinMode(BTN2, INPUT_PULLUP);
  myServo.attach(SERVO);        // Attach the servo
}

// Function to calculate the steps it takes to get to the right angle with the right timing
void moveServo(int startAngle, int endAngle, int duration){
  steps = abs(endAngle - startAngle);	// Number of steps
  delayTime = duration / steps; //Time per step in milliseconds
  
  // If the start angle is smaller than the end angle then move upwards to that angle
  if(startAngle < endAngle){
    for(int angle = startAngle; angle <= endAngle; angle++){
      // Write the current value of the angle to the servo
      myServo.write(angle);
      Serial.println(angle);
      // Delay it with the calculated time
      delay(delayTime);
    }
  // If the start angle is bigger than the end angle then move downwards to that angle
  } else {
    for(int angle = startAngle; angle >= endAngle; angle--){
      // Write the current value of the angle to the servo
      myServo.write(angle);
      Serial.println(angle);
      // Delay it with the calculated time
      delay(delayTime);
    }
  }
}

void loop()
{
  // Read the button states, because of the pull-up logic LOW is HIGH 
  btnState1 = !digitalRead(BTN1); // Pull-up logic: LOW is HIGH (pressed)
  btnState2 = !digitalRead(BTN2);
  
  // If both states are being pressed (low) then set the current mode to BOTH_BTNS_MODE
  if(btnState1 == HIGH && btnState2 == HIGH){
    currentMode = BOTH_BTNS_MODE;
  // If only btn1 is being pressed (low) then set the current mode to BTN1_MODE
  } else if(btnState1 == HIGH){
    currentMode = BTN1_MODE;
  } else if(btnState2 == HIGH){
  // If only btn2 is being pressed (low) then set the current mode to BTN2_MODE
    currentMode = BTN2_MODE;
  // If no buttons are being pressed then set the current mode to IDLE
  } else {
	 currentMode = IDLE; // Default mode when no buttons are pressed
  }
  
  // Start a timer for whatever current mode is chosen 
  unsigned long startTimer = millis(); 

   // Process the current mode
  switch (currentMode) {
	// Turn in 1 second from 0 to 120 degrees, hold still for 2 seconds, then return from 120 to 0 degrees within a second
    case BOTH_BTNS_MODE:
      Serial.println("Mode: BTN1 + BTN2");
      moveServo(0, 120, 1000);
      delay(2000); // 2 sec standstill
      moveServo(120, 0, 1000);
      break;
	// Turn in one second from 0 to 120 degrees, then return from 120 to 0 degrees within a second
    case BTN1_MODE:
      Serial.println("Mode: BTN1");
      moveServo(0, 120, 1000);
      moveServo(120, 0, 1000);
      break;
    // Turn in 500ms from 0 to 120 degrees, then return from 120 to 0 degrees within 500ms
    case BTN2_MODE:
      Serial.println("Mode: BTN2");
      moveServo(0, 120, 500);
      moveServo(120, 0, 500);
      break;
	// When no buttons are being pressed, do nothing 
    case IDLE:
    default:
      // Do nothing when idle
      break;
  }
	
  // Calculate the total time based on the start time of the current mode
  unsigned long endTimer = millis() - startTimer; // Calculate total elapsed time
  Serial.print("Mode duration: ");
  Serial.print(endTimer);
  Serial.println(" ms");
  
  delay(50); // Small delay for stability
}
