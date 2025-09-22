// Opdracht 5 - Alle mogelijke RGB-kleuren doorlopen met de RGB-led
// Gaat in stappen van 5 om het proces wat sneller te maken
// Geschreven door: Nina Schrauwen
// Bron: https://projecthub.arduino.cc/semsemharaz/interfacing-rgb-led-with-arduino-b59902

// Pins voor de RGB-led
const int RED_P = 2;
const int BLUE_P = 3;
const int GREEN_P = 4;

// Kleurwaardes (0–255)
int red;
int green;
int blue;

void setup()
{
  Serial.begin(9600); // verbinding met seriële monitor
  
  pinMode(RED_P, OUTPUT);
  pinMode(BLUE_P, OUTPUT);
  pinMode(GREEN_P, OUTPUT);
}

void loop()
{
  // Alle mogelijke combinaties van rood, groen en blauw doorlopen
  // Dit duurt even, ook al doen we stappen van 5
  for (red = 0; red <= 255; red += 5) {
    for (green = 0; green <= 255; green += 5) {
      for (blue = 0; blue <= 255; blue += 5) {
        setColor(red, green, blue);
      }
    }
  }
}

// Functie om de RGB-led in te stellen op de gekozen waardes
void setColor(int red, int green, int blue) {
  // Debug: laat de huidige kleurwaardes zien
  Serial.print("Kleur instellen - Rood: ");
  Serial.print(red);
  Serial.print(", Groen: ");
  Serial.print(green);
  Serial.print(", Blauw: ");
  Serial.println(blue);
  
  // Schrijf de waardes naar de juiste pinnen
  analogWrite(RED_P, red);
  analogWrite(GREEN_P, green);
  analogWrite(BLUE_P, blue);
}
