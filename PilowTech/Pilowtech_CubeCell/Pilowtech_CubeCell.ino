#include "LoRaWanMinimal_APP.h"
#include "Arduino.h"

//Set these OTAA parameters to match your app/node in TTN
uint8_t devEui[] = { 0x70, 0xB3, 0xD5, 0x7E, 0xD0, 0x06, 0x06, 0x05 };
uint8_t appEui[] = { 0x76, 0x15, 0x82, 0x23, 0x77, 0x16, 0x82, 0x50 };
uint8_t appKey[] = { 0x5F, 0x14, 0x5E, 0xCB, 0x37, 0x95, 0x2A, 0x26, 0xA3, 0x1B, 0xA1, 0xBE, 0x3C, 0x35, 0x29, 0x62 };
int temps = 180; // Indiquez dans cette ligne la fréquence d'envoi de données, en secondes. (Ne pas aller plus bas que 3minutes, soit 180sec)

uint16_t userChannelsMask[6]={ 0x00FF,0x0000,0x0000,0x0000,0x0000,0x0000 };
static uint8_t counter=0;
uint8_t lora_data[3];
uint8_t downlink ;

///////////////////////////////////////////////////
//Some utilities for going into low power mode
TimerEvent_t sleepTimer;
//Records whether our sleep/low power timer expired
bool sleepTimerExpired;

static void wakeUp()
{
  sleepTimerExpired=true;
}

static void lowPowerSleep(uint32_t sleeptime)
{
  sleepTimerExpired=false;
  TimerInit( &sleepTimer, &wakeUp );
  TimerSetValue( &sleepTimer, sleeptime );
  TimerStart( &sleepTimer );
  //Low power handler also gets interrupted by other timers
  //So wait until our timer had expired
  while (!sleepTimerExpired) lowPowerHandler();
  TimerStop( &sleepTimer );
}

///////////////////////////////////////////////////
void setup() {
  Serial.begin(115200);
  pinMode(GPIO7,OUTPUT);
  digitalWrite(GPIO7,LOW);
  LoRaWAN.begin(LORAWAN_CLASS, ACTIVE_REGION);
  
  //Enable ADR
  LoRaWAN.setAdaptiveDR(true);

  while (1) {
    Serial.print("Joining... ");
    LoRaWAN.joinOTAA(appEui, appKey, devEui);
    if (!LoRaWAN.isJoined()) {
      //In this example we just loop until we're joined, but you could
      //also go and start doing other things and try again later
      Serial.println("JOIN FAILED! Sleeping for 30 seconds");
      lowPowerSleep(30000);
    } else {
      Serial.println("JOINED");
      break;
    }
  }
}


///////////////////////////////////////////////////
void loop()
{
  counter++; 
  delay(10);
  uint8_t voltage = getBatteryVoltage()/50; //Voltage in %
  digitalWrite(GPIO7,HIGH);
  delay(1500);
  int sensorValue2 = analogRead(ADC2)/16;
  int sensorValue3 = analogRead(ADC3)/16;
  digitalWrite(GPIO7,LOW);
  Serial.printf("\nVal 2 : %d\n", sensorValue2);
  Serial.printf("\nVal 3 : %d\n", sensorValue3);

  Serial.printf("\nVoltage : %d\n", voltage);
  lora_data[0] = voltage;
  lora_data[1] = sensorValue2;
  lora_data[2] = sensorValue3; 
  //Now send the data. The parameters are "data size, data pointer, port, request ack"
  Serial.printf("\nSending packet with counter=%d\n", counter);
  Serial.printf("\nValue 1 to send : %d\n", lora_data[1]);

  //Here we send confirmed packed (ACK requested) only for the first two (remember there is a fair use policy)
  bool requestack=counter<2?true:false;
  if (LoRaWAN.send(sizeof(lora_data), lora_data, 1, requestack)) {
    Serial.println("Send OK");
  } else {
    Serial.println("Send FAILED");
  }

  lowPowerSleep(temps*1000);  
  delay(10);
}
