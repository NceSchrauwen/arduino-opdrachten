// Opdracht 4 - Meet de temperatuur en zet de ruwe ADC-waarde om naar °C (LM35)
// Geschreven door: Nina Schrauwen
// Bron: https://deepbluembedded.com/arduino-lm35-temperature-sensor-interfacing/

const int TEMP = A0; // pin waar de sensor op zit

void setup()
{
  // Start seriële communicatie om waarden te kunnen volgen in de monitor
  Serial.begin(9600);
}

void loop()
{
  int adcValue = analogRead(TEMP);  // lees de rauwe ADC-waarde
  float voltage = ((adcValue * 5.0) / 1023.0) * 1000;  
  // zet ADC-waarde om naar spanning → nodig om temperatuur te kunnen berekenen

  float tempC = voltage / 10;  
  // LM35 geeft 10mV per graad, dus spanning delen door 10 = temperatuur in °C

  // Print temperatuur in seriële monitor
  Serial.print("Temp is: ");
  Serial.print(tempC);
  Serial.print("\xB0");
  Serial.println("C");
  
  delay(1000); // korte pauze zodat waarden niet constant voorbij vliegen
}
