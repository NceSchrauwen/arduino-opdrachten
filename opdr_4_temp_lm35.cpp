// Opdracht 4 - Detect the temperature and convert raw ADC value to temp in Celcius (lm35 used)
// Written by: Nina Schrauwen
// Bron: https://lastminuteengineers.com/tmp36-temperature-sensor-arduino-tutorial/ ( https://arduinopoint.com/lm35-arduino-project/ )

// Define constant variables
const int TEMP = A0;

void setup()
{
  //Begin serial communication to be able to track console output
  Serial.begin(9600);
}

void loop()
{
  int adcValue = analogRead(TEMP); //raw adc value
  float voltage = (adcValue / 1023.0) * 5.0; // converting adc to voltage 
  
  //converting voltage into degree Celcius (subtracts the 500mV offset of the TMP36 and the 100 multiplies to convert volts to millivolts)
  float tempC = voltage * 100;  // LM35 Calculation

  // Debug print to keep track of the temp in the serial monitor
  Serial.print("Temp is: ");
  Serial.print(tempC);
  Serial.print("\xB0"); // Degree symbol
  Serial.println("C");
  
  // Delay so you don't have constant temp readings
  delay(5000);
}
