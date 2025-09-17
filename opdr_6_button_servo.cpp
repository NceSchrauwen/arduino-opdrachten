// Opdracht 6 - Servo laten bewegen van 0 naar 120 graden en terug in verschillende varianten en snelheden
// Geschreven door: Nina Schrauwen 
#include <Servo.h> 

Servo myServo; // Servo object aanmaken

// Pin definities
const int BTN1 = 3;
const int BTN2 = 4;
const int SERVO = 2;

// Verschillende modes (welke knop(pen) actief zijn)
enum Mode {
  IDLE,          // Geen knop ingedrukt
  BTN1_MODE,     // Alleen knop 1
  BTN2_MODE,     // Alleen knop 2
  BOTH_BTNS_MODE // Beide knoppen tegelijk
};

// Globale variabelen
Mode currentMode = IDLE; 
int btnState1 = 0;
int btnState2 = 0;
int angle;
int steps;
int delayTime;

void setup()
{
  Serial.begin(9600);         // Seriële monitor starten
  pinMode(BTN1, INPUT_PULLUP); // Knop 1 op pull-up
  pinMode(BTN2, INPUT_PULLUP); // Knop 2 op pull-up
  myServo.attach(SERVO);       // Servo verbinden met pin
}

// Functie om de servo stap voor stap te bewegen
// startAngle = beginstand
// endAngle   = eindstand
// duration   = hoelang de beweging totaal moet duren
// mode       = welke modus actief is (voor de stopconditie)
void moveServo(int startAngle, int endAngle, int duration, Mode mode) {
  steps = abs(endAngle - startAngle);    // Aantal graden verschil
  delayTime = duration / steps;          // Tijd per stap
  int stepDir = (startAngle < endAngle) ? 1 : -1; // Richting bepalen (oplopend of aflopend)

  // Van startAngle naar endAngle bewegen
  for (int angle = startAngle; angle != endAngle + stepDir; angle += stepDir) {
    // Knopstatussen uitlezen (pull-up omgedraaid)
    bool b1 = !digitalRead(BTN1);
    bool b2 = !digitalRead(BTN2);

    // Per modus checken of de vereiste knop(pen) nog wel ingedrukt zijn
    if (mode == BTN1_MODE && !b1) return;          // Stop als knop 1 losgelaten wordt
    if (mode == BTN2_MODE && !b2) return;          // Stop als knop 2 losgelaten wordt
    if (mode == BOTH_BTNS_MODE && !(b1 && b2)) return; // Stop als één van de 2 losgelaten wordt

    myServo.write(angle);   // Servo bewegen naar huidige stap
    delay(delayTime);       // Even wachten zodat beweging op tijd klopt
  }
}

void loop() {
  // Knopstatussen uitlezen (LOW = ingedrukt, dus omkeren met !)
  btnState1 = !digitalRead(BTN1);
  btnState2 = !digitalRead(BTN2);
  
  // Modus bepalen op basis van de knoppen
  if (btnState1 && btnState2) {
    currentMode = BOTH_BTNS_MODE;
  } else if (btnState1) {
    currentMode = BTN1_MODE;
  } else if (btnState2) {
    currentMode = BTN2_MODE;
  } else {
    currentMode = IDLE;
  }

  unsigned long startTimer = millis(); // Tijdmeting starten

  // Actie per modus
  switch (currentMode) {
    case BOTH_BTNS_MODE:
      Serial.println("Mode: BTN1 + BTN2");
      moveServo(0, 120, 1000, BOTH_BTNS_MODE); // Naar 120 in 1 seconde

      // 2 seconden vasthouden (maar stoppen als knoppen losgelaten worden)
      {
        unsigned long holdStart = millis();
        while (millis() - holdStart < 2000) {
          bool b1 = !digitalRead(BTN1);
          bool b2 = !digitalRead(BTN2);
          if (!(b1 && b2)) {
            Serial.println("Knoppen los tijdens vasthouden -> stoppen.");
            return;
          }
        }
      }

      moveServo(120, 0, 1000, BOTH_BTNS_MODE); // Terug naar 0 in 1 seconde
      break;
    
    case BTN1_MODE:
      Serial.println("Mode: BTN1");
      moveServo(0, 120, 1000, BTN1_MODE); // Naar 120 in 1 seconde
      moveServo(120, 0, 1000, BTN1_MODE); // Terug in 1 seconde
      break;
	
    case BTN2_MODE:
      Serial.println("Mode: BTN2");
      moveServo(0, 120, 500, BTN2_MODE);  // Naar 120 in 0,5 seconde
      moveServo(120, 0, 500, BTN2_MODE);  // Terug in 0,5 seconde
      break;
	
    case IDLE:
    default:
      // Doe niks als er geen knoppen worden ingedrukt
      break;
  }
	
  // Totale tijd van de modus meten
  unsigned long endTimer = millis() - startTimer;
  Serial.print("Mode duration: ");
  Serial.print(endTimer);
  Serial.println(" ms");
	
  delay(50); // Kleine vertraging zodat het stabiel blijft draaien
}
