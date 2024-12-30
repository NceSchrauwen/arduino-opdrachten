// Opdracht 5 - Code to cycle through all the possible rgb colors of the rgb led, done in steps of five to speed the process up a bit
// Written by: Nina Schrauwen 
// Bron: https://projecthub.arduino.cc/semsemharaz/interfacing-rgb-led-with-arduino-b59902

// Define constant variables
const int RED_P = 2;
const int BLUE_P = 3;
const int GREEN_P = 4;
// Define global variables
int red;
int green;
int blue;

void setup()
{
  // Make a connection to the serial monitor to be able to produce console output
  Serial.begin(9600);
  // Define inputs to the corresponding pins
  pinMode(RED_P, OUTPUT);
  pinMode(BLUE_P, OUTPUT);
  pinMode(GREEN_P, OUTPUT);
}

void loop()
{
  // The blue will start then will move through all possibel green/blue color variations and then all red/green/blue combinations. (Will take some time even in steps of 5)
  // To cycle through all the red values
  for(red = 0; red <= 255; red += 5){
	// To cycle through all the green values
    for(green = 0; green <= 255; green += 5){
	  // To cycle through all the green values
      for(blue = 0; blue <= 255; blue += 5){
      	setColor(red, green, blue);
      }
    }
  }
}

// Function to set the color according to the passed color values 
void setColor(int red, int green, int blue) {
  //Debug print to keep track of the process of changing the values because it takes a long time to get through all the possible values
  Serial.print("Setting Colors - Red: ");
  Serial.print(red);
  Serial.print(", Green: ");
  Serial.print(green);
  Serial.print(", Blue: ");
  Serial.println(blue);
  
  //Assign the color value to the corresponding color pin to turn on the right color(s) in the right value(s)
  analogWrite(RED_P, red);
  analogWrite(GREEN_P, green);
  analogWrite(BLUE_P, blue);
}
