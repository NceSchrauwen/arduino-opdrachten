// Opdracht 3 - 7 LEDs geleidelijk aansturen met een potentiometer
// Geschreven door: Nina Schrauwen

// LED-pinnen
const int LEDPINS[] = {2, 3, 4, 5, 6, 7, 8};
int pot = A5; // potentiometer moet analoog zijn

void setup()
{	
  Serial.begin(9600); // seriële monitor starten
  
  // Alle LED-pinnen als output instellen
  for (int i = 0; i < 7; i++) {
    pinMode(LEDPINS[i], OUTPUT);
  }
}

void loop()
{
  // Lees waarde van de potentiometer (0–1023)
  int potValue = analogRead(pot);

  // Bereken hoeveel LEDs aan moeten staan
  int numLedsOn = map(potValue, 0, 1023, 0, 7);
  
  // Debug: laat potmeterwaarde en aantal LEDs zien
  Serial.print("Potmeter: ");
  Serial.print(potValue);
  Serial.print(" | LEDs aan: ");
  Serial.println(numLedsOn);
  
  // LEDs aan/uit zetten afhankelijk van de potmeterstand
  for (int i = 0; i < 7; i++) {
    if (i < numLedsOn) {
      digitalWrite(LEDPINS[i], HIGH);
    } else {
      digitalWrite(LEDPINS[i], LOW);
    }
  }
  
  delay(100); // korte pauze voor stabiliteit
}
