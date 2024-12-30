// Opdracht 8 - Code to program lights according to buttons on the remote, also for the speed
// Written by: Nina Schrauwen
// https://forum.arduino.cc/t/using-millis-for-timing-a-beginners-guide/483573/2

// Include library for IR remote
#include <IRremote.hpp>

// Define the constant variables 
const int RECV = 4;
const int LED = 7;
const int LED2 = 9;
const int LED3 = 11;
const int LED4 = 13;
const bool isLEDOn = true;
const bool isLED2On = true;
// Define the global variables
unsigned long irCode;
unsigned long currentMillis;
unsigned long previousMillis = 0;
unsigned long previousMillisForBlink = 0;
unsigned long previousMillisForBlink3 = 0;
unsigned long previousMillisForBlink4 = 0;
int currentLed;
int blinkSpeed;
bool isLED3On = false;
bool isLED4On = false;
// Variables for controlling the default LEDs
unsigned long interval = 1000;  // Default blink speed for LEDs 1 and 2 
// Create an IR receiver object and assign it to the RECV pin      
IRrecv irrecv(RECV);


void setup()
{
  // Set the LED pins as output
  pinMode(LED, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  // Initialize the IR receiver
  irrecv.enableIRIn();
  // Start serial communication
  Serial.begin(9600);
}

//Function to led the correct leds blink at the correct blink interval
void setBlink(bool ledBool, int blinkInterval, int ledPin, unsigned long &previousMillis) {
	//If the state of the led is true start the timer
    if (ledBool) {
        unsigned long currentMillis = millis();
		//When the desired interval has passed toggle the ledstate between HIGH and LOW 
        if (currentMillis - previousMillis >= blinkInterval) {
            previousMillis = currentMillis;
            digitalWrite(ledPin, !digitalRead(ledPin));  // Toggle LED state
        }
    }
}

void loop()
{
  // Get the current time using millis() and store it within the currentMillis variable 
  currentMillis = millis();
  
  // Always run the function because the function will decide if the led should be on or not based on the variables that are set
  // You pass along the boolean for the validation, interval of blinking, which led it is, and the previous time interval
  setBlink(isLEDOn, interval, LED, previousMillis);
  setBlink(isLED2On, interval, LED2, previousMillisForBlink);
  setBlink(isLED3On, blinkSpeed, LED3, previousMillisForBlink3);
  setBlink(isLED4On, blinkSpeed, LED4, previousMillisForBlink4);
  
  // If the receiver receives a response
  if (irrecv.decode()) {
	// Decode the response and assign it to the irCode variable
    irCode = irrecv.decodedIRData.decodedRawData;
    // Print the IR code in hexadecimal format
    Serial.print("Received IR Code: ");
    Serial.println(irCode, HEX);
    
	// Switch to determine which button is being pressed (1 t/m 4)
    switch(irCode){
     case 0xBA45FF00:  //button 1
      blinkSpeed = 100;  //set blinkspeed to 100ms
      break;
	  
     case 0xB946FF00:  //button 2
      blinkSpeed = 200; //set blinkspeed to 200ms
      break;
	  
     case 0xB847FF00:  //button 3
      blinkSpeed = 300;  //set blinkspeed to 300ms
	  // If led 4 is not on
	  if(!isLED4On){
		  // If led 3 is on
		  if(isLED3On){
			isLED3On = false; // Set the boolean to false 
			digitalWrite(LED3, LOW); // Power off led 3
		  } else {
			isLED3On = true; // Set the boolean to true, causing led 3 to turn on
		  }
	  }
	  break;
	  
     case 0xBB44FF00:  //button 4
	  blinkSpeed = 400;  //set blinkspeed to 300ms
	  // If led 3 is not on
      if(!isLED3On){
		  // If led 4 is on
		  if(isLED4On){
			isLED4On = false; // Set the boolean to false
			digitalWrite(LED4, LOW); // Power off led 3
		  } else {
			isLED4On = true;  // Set the boolean to true, causing led 4 to turn on
	      }
	  }
	  break;
	  
    }
	
    // Continue receiving signals 
    irrecv.resume();  
  }
  
  // Debug print the blink speed to make sure it's correct
  Serial.print('Blinkspeed: ');
  Serial.println(blinkSpeed);
	
  // Small delay for stability 
  delay(50);
}
