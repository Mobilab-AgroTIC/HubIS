#include "LoRaWanMinimal_APP.h"
#include "Arduino.h"


///////////////////////////////////////////////////
void setup() {
  Serial.begin(115200);
  pinMode(GPIO7,OUTPUT);
  digitalWrite(GPIO7,LOW);
  pinMode(GPIO2, OUTPUT_PULLUP);
  digitalWrite(GPIO2, HIGH);
}


///////////////////////////////////////////////////
void loop()
{
  digitalWrite(GPIO7,HIGH);
  delay(1000); //temps nécessaire pour la mise en route des capteurs
  uint8_t voltage = getBatteryVoltage()/50; //Voltage in %
 
  int sensorValue2 = digitalRead(GPIO2);
  Serial.printf("\nVal 2 : %d\n", sensorValue2);
  Serial.printf("\nVoltage : %d\n", voltage);

}
