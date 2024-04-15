#include "LoRaWanMinimal_APP.h"
#include "Arduino.h"


///////////////////////////////////////////////////
void setup() {
  Serial.begin(115200);
  pinMode(GPIO7,OUTPUT);
  digitalWrite(GPIO7,LOW);
}


///////////////////////////////////////////////////
void loop()
{

  delay(100);
  uint8_t voltage = getBatteryVoltage()/50; //Voltage in %
  digitalWrite(GPIO7,HIGH);
  delay(1500);
  int sensorValue2 = analogRead(ADC2);
  int sensorValue3 = analogRead(ADC3);
  digitalWrite(GPIO7,LOW);
  
  Serial.printf("\voltage : %d\n", voltage);
  Serial.printf("\nVal 2 : %d\n", sensorValue2);
  Serial.printf("\nVal 3 : %d\n", sensorValue2);

  delay(100);
}
