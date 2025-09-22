// Opdracht 1 - Knight Rider lichtsequentie (LEDs heen en weer laten lopen)
// Geschreven door: Nina Schrauwen

// LED-pinnen
const int LEDS[] = {2, 3, 4, 5, 6, 7, 8, 9};

void setup()
{	
  // Alle LED-pinnen als output instellen
  for (int i = 0; i <= 7; i++) {
    pinMode(LEDS[i], OUTPUT);
  }
}

// LEDs van links naar rechts laten lopen
void to() {
  for (int i = 0; i < 7; i++) {
    // Uiteinde → LED blijft even aan voor vloeiende overgang
    if (i == 7) {
      digitalWrite(LEDS[i], HIGH);
      delay(75);
    } else {
      digitalWrite(LEDS[i], HIGH);
      delay(75);
      digitalWrite(LEDS[i], LOW);
      delay(75);
    } 
  }
}

// LEDs van rechts naar links laten lopen
void from() {
  for (int i = 7; i >= 0; i--) {
    // Uiteinde → LED blijft even aan
    if (i == 0) {
      digitalWrite(LEDS[i], HIGH);
      delay(75);
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
  // Wissel heen en weer voor het Knight Rider-effect
  to();
  from();
}
