// Opdracht 8 - Leds programmeren met IR afstandsbediening + knippersnelheid
// Geschreven door: Nina Schrauwen
// https://forum.arduino.cc/t/using-millis-for-timing-a-beginners-guide/483573/2

#include <IRremote.hpp>

// IR receiver pin
const int RECV = 11;

// Struct: koppelt IR-code ↔ knopnummer ↔ LED-pin
struct ButtonMap {
  unsigned long irCode;
  int buttonNumber;
  int ledPin;
};

// Mapping van 4 knoppen met bijbehorende LED-pins
ButtonMap buttonMap[4] = {
  {0xBA45FF00, 1, 2},   // Knop 1 → LED pin 2
  {0xB946FF00, 2, 6},   // Knop 2 → LED pin 6
  {0xB847FF00, 3, 9},   // Knop 3 → LED pin 9
  {0xBB44FF00, 4, 10}   // Knop 4 → LED pin 10
};

// Globale variabelen
int activeLEDs[2] = {-1, -1};                 // max. 2 actieve LEDs (indices uit buttonMap)
unsigned long previousMillis[4] = {0,0,0,0};  // timer per LED
int blinkSpeeds[4] = {0,0,0,0};               // snelheid per LED
bool ledStates[4] = {false,false,false,false}; // huidige status (aan/uit)
int globalBlinkSpeed = 500;                   // standaard = 500ms

// IR receiver object
IRrecv irrecv(RECV);

// ---------------------------------------------------------------------------
// Setup
// ---------------------------------------------------------------------------
void setup() {
  Serial.begin(9600);  
  IrReceiver.begin(RECV, ENABLE_LED_FEEDBACK); 

  // LED-pins instellen als output en uitzetten
  for (int i = 0; i < 4; i++) {
    pinMode(buttonMap[i].ledPin, OUTPUT);
    digitalWrite(buttonMap[i].ledPin, LOW);
  }
  
  // Random seed, A0 is leeg dus bruikbaar
  randomSeed(analogRead(A0));   

  // Kies 2 verschillende random LEDs en zet ze aan
  int first = random(0, 4);
  int second;
  do {
    second = random(0, 4);
  } while (second == first);

  toggleLED(first);  
  toggleLED(second);  

  Serial.print("Startup LEDs: ");
  Serial.print(buttonMap[first].buttonNumber);
  Serial.print(" en ");
  Serial.println(buttonMap[second].buttonNumber);

  Serial.println("IR ontvanger klaar...");
}

// ---------------------------------------------------------------------------
// LED togglen of snelheid aanpassen
// ---------------------------------------------------------------------------
void toggleLED(int mapIndex) {
  int ledPin = buttonMap[mapIndex].ledPin;
  int buttonNumber = buttonMap[mapIndex].buttonNumber;

  // Check of LED al actief is
  bool alreadyActive = false;
  for (int i = 0; i < 2; i++) {
    if (activeLEDs[i] == mapIndex) {
      alreadyActive = true;
      break;
    }
  }

  if (alreadyActive) {
    // Als LED actief is → snelheid aanpassen
    globalBlinkSpeed = buttonNumber * 100;  // knopnummer × 100ms
    Serial.print("Nieuwe snelheid: ");
    Serial.println(globalBlinkSpeed);
  } else {
    // Nog niet actief → toevoegen
    if (activeLEDs[0] != -1 && activeLEDs[1] != -1) {
      // Al 2 actief → oudste verwijderen
      int removed = activeLEDs[0];
      digitalWrite(buttonMap[removed].ledPin, LOW);
      ledStates[removed] = false;

      // Schuif door en voeg nieuwe toe
      activeLEDs[0] = activeLEDs[1];
      activeLEDs[1] = mapIndex;
      Serial.print("LED ");
      Serial.print(buttonMap[removed].buttonNumber);
      Serial.print(" verwijderd, LED ");
      Serial.print(buttonNumber);
      Serial.println(" toegevoegd");
    }
    else if (activeLEDs[0] == -1) {
      activeLEDs[0] = mapIndex;
      previousMillis[mapIndex] = millis();
      ledStates[mapIndex] = false;
      Serial.print("LED ");
      Serial.print(buttonNumber);
      Serial.println(" toegevoegd");
    }
    else {
      activeLEDs[1] = mapIndex;
      previousMillis[mapIndex] = millis();
      ledStates[mapIndex] = false;
      Serial.print("LED ");
      Serial.print(buttonNumber);
      Serial.println(" toegevoegd");
    }
  }
}

// ---------------------------------------------------------------------------
// LEDs updaten op basis van globale snelheid
// ---------------------------------------------------------------------------
void updateLEDs() {
  unsigned long currentMillis = millis();
  for (int i = 0; i < 2; i++) {
    int mapIndex = activeLEDs[i];
    if (mapIndex != -1) {
      if (currentMillis - previousMillis[mapIndex] >= globalBlinkSpeed) {
        previousMillis[mapIndex] = currentMillis;
        ledStates[mapIndex] = !ledStates[mapIndex];
        digitalWrite(buttonMap[mapIndex].ledPin, ledStates[mapIndex] ? HIGH : LOW);
      }
    }
  }
}

// ---------------------------------------------------------------------------
// Main loop
// ---------------------------------------------------------------------------
void loop() {
  if (IrReceiver.decode()) {
    unsigned long irCode = IrReceiver.decodedIRData.decodedRawData;
    Serial.print("Ontvangen IR Code: ");
    Serial.println(irCode, HEX);

    // Check of de IR-code overeenkomt met de mapping
    for (int i = 0; i < 4; i++) {
      if (irCode == buttonMap[i].irCode) {
        toggleLED(i);
      }
    }

    IrReceiver.resume(); // klaarmaken voor volgende signaal
  }

  // LEDs updaten, ook zonder input
  updateLEDs();
}
