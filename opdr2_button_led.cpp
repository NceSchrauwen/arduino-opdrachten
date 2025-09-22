// Opdracht 2 - LED aan/uit schakelen met een drukknop (toggle)
// Geschreven door: Nina Schrauwen

// Pinnen
const int BTN = 2;
const int LED = 11;
const int DELAY = 50;

// Variabelen
int btnStatus = LOW;
int lastBtnStatus = LOW;
int counter = 0;

void setup()
{
  Serial.begin(9600); // seriële monitor starten

  pinMode(LED, OUTPUT);
  pinMode(BTN, INPUT_PULLUP); // knop als pull-up → standaard HIGH
}

void loop()
{
  // Met INPUT_PULLUP is de knop normaal HIGH en wordt LOW bij indrukken.
  // Met !digitalRead(BTN) draaien we dit om: HIGH = ingedrukt, LOW = losgelaten.
  btnStatus = !digitalRead(BTN);
  
  // Alleen tellen bij overgang van los → ingedrukt
  if (btnStatus == HIGH && lastBtnStatus == LOW) {
    counter++;
  }
  
  // Even = LED uit, oneven = LED aan
  if (counter % 2 == 0) {
    digitalWrite(LED, LOW);
    Serial.println("LED UIT");
  } else {
    digitalWrite(LED, HIGH);
    Serial.println("LED AAN");
  }
  
  lastBtnStatus = btnStatus; // huidige status opslaan voor volgende check
  
  delay(DELAY); // korte pauze voor stabiliteit
}
