/*
  Measure a distance (at 20°C) with the HCSR04 sensor,
  send it in LoRa communication with RN2483 chip and through The Things Network, 
  turn off the sensor and put in sleep the Arduino and the RN2483 chipcard for 70seconds.
  
  Created 22 April 2020 by simon Moinard (simmoinard@gmail.com)   
  This example code is in the public domain.

  CABLES CONNEXION
 *      RN2483      <-->       Arduino Pro Mini 3.3V
 *    
 *     UART_TX (6)   <-->   5
 *     UART_RX (7)   <-->   6
 *     RESET (32)    <-->   10
 *     VDD (34)      <-->   VCC 3.3V
 *     GND (33)      <-->   Gnd
 *
 *
 *       HCSR04     <-->    BC547 Transistor   <-->     Arduino Pro Mini 5V
 *   
 *     Vcc          <-->        Collector          
 *     Trigger      <----------------------------->     2
 *     Echo         <----------------------------->     3
 *     GND          <----------------------------->     GND
 *                                 Base        <-->     7
 *                                Emitter      <-->     5V  
 *
*/

// **** INCLUDES *****
#include "LowPower.h"
#include <rn2xx3.h>
#include <TheThingsNetwork.h>
#include <SoftwareSerial.h>

// **** Serial communication ****
SoftwareSerial loraSerial(5, 6); // RX, TX
#define debugSerial Serial
rn2xx3 myLora(loraSerial);

// **** Things Network configuration ****
#define freqPlan TTN_FP_EU868
const char *appEui = "70B3D57ED000F8A4";
const char *appKey = "53AC1493AC434949BBFA8A627C88ECA0";
TheThingsNetwork ttn(loraSerial, debugSerial, freqPlan, 10);


const int TRANSISTOR_PIN = 4;
const int RESET_PIN = 10;

void setup()
{
  // HCSR04 Setup
  pinMode(TRANSISTOR_PIN,OUTPUT);
  digitalWrite(TRANSISTOR_PIN,LOW);

  // RN2483 Setup
  loraSerial.begin(9600);
  debugSerial.begin(9600);
  delay(500);
  
  pinMode(RESET_PIN, OUTPUT); // Reset of RN2483
  digitalWrite(RESET_PIN, LOW);
  delay(500);
  digitalWrite(RESET_PIN, HIGH);
  myLora.autobaud(); // le baud passe à 9600

  // Wait a maximum of 10s for Serial Monitor, then display chip information
  while (!debugSerial && millis() < 2000)
    ;
  // Set callback for incoming messages
  ttn.onMessage(message);
  
  debugSerial.println("-- STATUS");
  ttn.showStatus();
  debugSerial.println("-- JOIN");
  ttn.join(appEui, appKey);
}


void loop() 
{
  //------- MEASURE -------


  //------- RECEIVE DATA ------- 
  ttn.poll();
  debugSerial.println("MSG");
  delay(1000);

  //------- SLEEP MODE -------
  ttn.sleep(100000000);  //sleep for 100 000 000 millisec, 1660min, 30hours
  for (int i = 0; i <= 1; i++) {
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);  
  }
  ttn.wake();
  delay(1000);

}

void message(const uint8_t *payload, size_t size, port_t port)
{
  debugSerial.println("-- MESSAGE");
  debugSerial.print("Received " + String(size) + " bytes on port " + String(port) + ":");
  char test[2];
  for (int i = 0; i < size; i++)
  {
    debugSerial.print(" " + String(payload[i]));
  }
  if (payload[0] == 1){
    debugSerial.print("un!!");
    digitalWrite(13,HIGH);
    delay(500);
    digitalWrite(13,LOW);
    delay(100);
  }
}
