// Opdracht 3 - Code to gradually turn on all the leds while turning the potentiometer
// Written by: Nina Schrauwen

// Define constant variables
const int LEDPINS[]= {2, 3, 4, 5, 6, 7, 8};
int pot = A5; // Has to be tied to an analog value

void setup()
{	
  // Setting up a serial monitor to be able to monitor console output
  Serial.begin(9600);
  // Loop through and define the outputs of the ledpins
  for(int i = 0; i < 7; i++){
  	pinMode(LEDPINS[i], OUTPUT);
  }
}

void loop()
{
  // Read the value of the potentiometer
  int potValue = analogRead(pot);
  // Determine how many leds should be on based on the value of the potentiometer
  int numLedsOn = map(potValue, 0, 1023, 0, 7);
  
  // Debug printing to track the potentiometer value
  Serial.print("Potentiometer Value: ");
  Serial.print(potValue);
  Serial.print(" | LEDs On: ");
  Serial.println(numLedsOn);
  
  // Loop through all the ledpins
  for (int i = 0; i < 7; i++) {
      // If there are fewer leds on then calculated then turn those leds on
      if (i < numLedsOn) {
        digitalWrite(LEDPINS[i], HIGH);
      // If there are too many leds on, turn those leds off
      } else {
        digitalWrite(LEDPINS[i], LOW);
      }
    }
  
  delay(100); // Small delay for stability
}
