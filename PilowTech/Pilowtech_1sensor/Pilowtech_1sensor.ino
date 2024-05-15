#include "LoRaWanMinimal_APP.h"
#include "Arduino.h"

//CLEFS A MODIFIER SELON TTN
const char* APP_EUI = "0000000000000000";                     
const char* DEV_EUI = "0000000000000000";                     
const char* APP_Key = "00000000000000000000000000000000";     


int temps = 300; // Indiquez dans cette ligne la fréquence d'envoi de données, en secondes. (Ne pas aller plus bas que 3minutes, soit 180sec)

uint16_t userChannelsMask[6]={ 0x00FF,0x0000,0x0000,0x0000,0x0000,0x0000 };
static uint8_t counter=0;
uint8_t lora_data[3];
uint8_t downlink ;


const int AppEUI_len = strlen(APP_EUI);
const int DevEUI_len = strlen(DEV_EUI);
const int AppKey_len = strlen(APP_Key);

byte AppEUI_clefConvertie[8];
byte DevEUI_clefConvertie[8];
byte AppKey_clefConvertie[16];

uint8_t appEui[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
uint8_t devEui[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
uint8_t appKey[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };


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


void convertirClef(const char* clef, byte* clefConvertie, int longueur) {
    for (int i = 0; i < longueur; i += 2) {
        char byteStr[3] = {clef[i], clef[i + 1], '\0'};
        clefConvertie[i / 2] = strtol(byteStr, NULL, 16);
    }
}

void remplirTableau(uint8_t* tableau, byte* clefConvertie, int longueur) {
    for (int i = 0; i < longueur / 2; i++) {
        tableau[i] = clefConvertie[i];
    }
}

///////////////////////////////////////////////////
void setup() {
  Serial.begin(115200);

  
  convertirClef(APP_EUI, AppEUI_clefConvertie, AppEUI_len);
  convertirClef(DEV_EUI, DevEUI_clefConvertie, DevEUI_len);
  convertirClef(APP_Key, AppKey_clefConvertie, AppKey_len);
      
  remplirTableau(appEui, AppEUI_clefConvertie, AppEUI_len);
  remplirTableau(devEui, DevEUI_clefConvertie, DevEUI_len);
  remplirTableau(appKey, AppKey_clefConvertie, AppKey_len);

  
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
  int sensorValue2 = analogRead(ADC2);
  digitalWrite(GPIO7,LOW);
  Serial.printf("\nVal 2 : %d\n", sensorValue2);

  Serial.printf("\nVoltage : %d\n", voltage);
  lora_data[0] = voltage;
  lora_data[1] = highByte(sensorValue2);
  lora_data[2] = lowByte(sensorValue2);

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
