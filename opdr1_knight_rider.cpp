// Opdracht 1 - Blinking leds sequence like knight rider car lights
// Written by: Nina Schrauwen

// Define constant variables
const int LEDS[] = {2, 3, 4, 5, 6, 7, 8, 9};


void setup()
{	
  // Define the ledpin outputs by looping through each of them
  for(int i = 0; i <= 7; i++){
    pinMode(LEDS[i], OUTPUT);
  }
}

//Function to light up the leds from left to right 
void to(){
  // Loop through all ledpins
  for(int i = 0; i < 7; i++){
    // If it has reached the end don't turn it off 
	// If it would go off at the end and then on again the other way around it would blink twice at the end which would not be a smooth transition
    if(i == 7){
      digitalWrite(LEDS[i], HIGH);
      delay(75);
    // If it has not reached the end turn it on and off 
    } else {
      digitalWrite(LEDS[i], HIGH);
      delay(75);
      digitalWrite(LEDS[i], LOW);
      delay(75);
    } 
  }
}

//Function to light up the leds from right to left 
void from(){
  // If it has reached the end don't turn it off 
  // If it would go off at the end and then on again the other way around it would blink twice at the end which would not be a smooth transition
  for(int i = 7; i >= 0; i--){
    if(i == 0){
      digitalWrite(LEDS[i], HIGH);
      delay(75);
    // It has come either from the end or is somewhere in the middle so just turn on and off
    } else {
      digitalWrite(LEDS[i], HIGH);
      delay(75);
      digitalWrite(LEDS[i], LOW);
      delay(75);	
    }
  }
}

void loop()
{
  // Call the functions within the loop so it can move back and forth on repeat like the car lights in knight rider
  to();
  from();
}
