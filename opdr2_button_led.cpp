// Opdracht 2 - Code to make the Led go on by pressing once, press on it again and it turns off
// Written by: Nina Schrauwen

// Define constant variables
const int BTN = 2;
const int LED = 11;
const int DELAY = 50;
// Define global variables
int btnStatus = LOW;
int lastBtnStatus = LOW;
int counter = 0;

void setup()
{
  // Start serial communication to be able to monitor console output
  Serial.begin(9600);
  // Define input/output with their pins
  pinMode(LED, OUTPUT);
  // The button is set up as a pull-up so i'll define it as such
  pinMode(BTN, INPUT_PULLUP);
}

void loop()
{
  // INPUT_PULLUP reads HIGH when the button is unpressed and LOW when pressed.
  // Using !digitalRead(BTN) inverts this behavior so that HIGH represents a button press 
  // and LOW represents a button release, ensuring the rest of the logic works as intended.
  btnStatus = !digitalRead(BTN);
  
  // If the current status is high and the old status is low then add to the counter
  if(btnStatus == HIGH && lastBtnStatus == LOW){
	// Add one value to the counter when the condition is true
    counter++;
  }
  
  // If the count is even turn the led off
  if(counter % 2 == 0){
  	digitalWrite(LED, LOW);
    Serial.println("Led OFF");
  // If it's uneven turn the led on
  } else {
    digitalWrite(LED, HIGH);
    Serial.println("Led ON");
  }
  
  // Update the last button status to the current button status
  lastBtnStatus = btnStatus;
  
  // Small delay for stability
  delay(DELAY);
  
}
