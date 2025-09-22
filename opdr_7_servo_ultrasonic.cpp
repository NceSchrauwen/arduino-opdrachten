// Opdracht 7 - Ultrasoon sensor stuurt de servo binnen bepaalde grenzen
// Geschreven door: Nina Schrauwen

#include <Servo.h>

// Constante variabelen
const int TRIG = 12;
const int ECHO = 13;
const int SERVO = 2;

// Globale variabelen
long duration;
int distance;
int angle;

Servo servo; // Servo object

void setup()
{
  Serial.begin(9600);

  // Ultrasoon sensor instellen
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  
  servo.attach(SERVO);
  servo.write(0);  // rustpositie = 0 graden
}

void loop()
{
  // Schone puls genereren → trigger kort laag
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  // Meetpuls versturen
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  
  // Lengte van echo signaal meten
  duration = pulseIn(ECHO, HIGH);
  
  // Omgerekend naar afstand in cm
  distance = duration * 0.0344 / 2;
  
  // Debug: afstand in cm tonen
  Serial.print("Afstand: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  // Servo bewegen als afstand tussen 4 en 10 cm ligt
  if (distance >= 4 && distance <= 10) {
    // Map afstand (4–10 cm) naar servohoek (90–180 graden)
    angle = map(distance, 4, 10, 90, 180);
    servo.write(angle);
    Serial.print(angle);
    Serial.println(" graden");
  } else {
    // Buiten bereik → terug naar rustpositie
    servo.write(0);
  }
  
  delay(500); // korte pauze voor stabiliteit
}
