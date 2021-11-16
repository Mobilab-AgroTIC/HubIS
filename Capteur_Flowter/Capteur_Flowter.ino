/*
 * Mesure de distance avec le HCSR04 et envoi de la mesure en LoRa (RN2483) sur la plateforme The Things network, puis entre en sommeil.
 *    UART_TX (6)   <-->   5 
      UART_RX (7)   <-->   6 
      RESET (32)    <-->   10
      VDD (34)      <-->   3.3V
      GND (33)      <-->   Gnd
 *
 * Le 3.3V ne semble pas assez puissant pur établir une communnication RX/TX propre avec un baudrate de 57000 (de base). 
 * On se sert de la librairie rn2xx3.h pour changer le baudrate du RN à 9600, avec la fonction autobaud.
*/

// **** INCLUDES *****
#include "LowPower.h"
#include <rn2xx3.h>
#include <TheThingsNetwork.h>
#include <SoftwareSerial.h>

//Serial definition
#define debugSerial Serial
SoftwareSerial loraSerial(5, 6); // RX, TX
rn2xx3 myLora(loraSerial);

//TTN
int RESET_PIN =10;
#define freqPlan TTN_FP_EU868
const char *appEui = "70B3D57ED000F8A4";
const char *appKey = "75D677D2EE55359B9F4595E7CC2083DE";
TheThingsNetwork ttn(loraSerial, debugSerial, freqPlan, 10); //SF10

//Measure system
const int wakeUpPin = 2;
void wakeUp()
{
    // Just a handler for the pin interrupt.
}

void setup()
{
  //Setup system
  pinMode(wakeUpPin, INPUT);   
  pinMode(LED_BUILTIN, OUTPUT);

  //PARAMETRAGE TTN
  loraSerial.begin(9600);
  debugSerial.begin(9600);
  delay(1000);
  
  pinMode(RESET_PIN, OUTPUT); // Reset le RN2483
  digitalWrite(RESET_PIN, LOW);
  delay(500);
  digitalWrite(RESET_PIN, HIGH);
  myLora.autobaud(); // le baud passe à 9600
  // Wait a maximum of 10s for Serial Monitor
  while (!debugSerial && millis() < 2000)
    ;
  debugSerial.println("-- STATUS");
  ttn.showStatus();

  debugSerial.println("-- JOIN");
  ttn.join(appEui, appKey);
}


void loop() 
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(10);                      
  digitalWrite(LED_BUILTIN, LOW);
  int val = digitalRead(wakeUpPin);

  //------- SEND THE VALUE THROUGH TTN ------- 
  debugSerial.println("-- LOOP");
  byte payload[1];
  payload[0] = val;
  debugSerial.print('Value : ');
  debugSerial.println(payload[0]);
  ttn.sendBytes(payload, sizeof(payload), 1);
  delay(100);

  //------- SLEEP MODE -------
  ttn.sleep(4294967290);  //sleep for 100 000 000 millisec, 1660min, 30hours
  delay(100);
  for (int i = 0; i <= 1; i++) {
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);  
  }
  delay(100);
  debugSerial.println("sleep...");
  digitalWrite(LED_BUILTIN, HIGH);
  delay(10);                      
  digitalWrite(LED_BUILTIN, LOW);
  attachInterrupt(digitalPinToInterrupt(wakeUpPin), wakeUp, CHANGE);
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF); 
  delay(50);
  detachInterrupt(digitalPinToInterrupt(wakeUpPin)); 
  debugSerial.println("rebooting...");
  ttn.wake();
}
