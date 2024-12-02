//Resistance 10kOhm pour Cubecell AB02

#include "Arduino.h"
#define TRANSISTOR_PIN GPIO7

///////////////////////////////////////////////////
void setup() {
  Serial.begin(115200);
  pinMode(TRANSISTOR_PIN,OUTPUT);
  digitalWrite(TRANSISTOR_PIN,LOW);
}


///////////////////////////////////////////////////
void loop()
{

  delay(100);
  uint8_t voltage = getBatteryVoltage()/50; //Voltage in %
  digitalWrite(TRANSISTOR_PIN,HIGH);
  delay(1500);
  int sensorValue2 = analogRead(ADC2);
  int sensorValue3 = analogRead(ADC3);
  digitalWrite(TRANSISTOR_PIN,LOW);
  
  Serial.printf("\voltage : %d\n", voltage);
  Serial.printf("\nValeur broche 2 : %d\n", sensorValue2);
  Serial.printf("\nValeur broche 3 : %d\n", sensorValue3);

  delay(100);
}
