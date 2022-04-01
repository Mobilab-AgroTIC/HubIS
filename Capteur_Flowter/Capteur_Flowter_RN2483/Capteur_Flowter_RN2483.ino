

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
const char *appEui = "0000000000000000";
const char *appKey = "75D677D2EE55359B9F4595E7CC2083DE";
TheThingsNetwork ttn(loraSerial, debugSerial, freqPlan, 10); //SF10


void setup()
{
  //Setup system
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
  int val = digitalRead(A3);

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
  for (int i = 0; i < 20; i++) {
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);  
  }
  delay(10);
  ttn.wake();
}
