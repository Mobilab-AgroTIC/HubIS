#include "Arduino.h"
//14mA en actif - 10mA en veille
// Pb Battery : 0.7A
//LowPower - 
// MOSFET IRF520 de Velleman

#define PIN_TRANSISTOR GPIO2

//////////////////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(115200);
  pinMode(PIN_TRANSISTOR,OUTPUT);
  digitalWrite(PIN_TRANSISTOR,LOW);
}

//////////////////////////////////////////////////////////////////////////////
void loop(){
  delay(10);
  uint8_t voltage = getBatteryVoltage()/50; //Tension en %
  Serial.printf("\nVoltage : %d\n", voltage);

  digitalWrite(PIN_TRANSISTOR,HIGH);
  Serial.print("HIGH");
  delay(5000);
  digitalWrite(PIN_TRANSISTOR,LOW);
  Serial.print("LOW");
  delay(5000);  

}
