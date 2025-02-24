#include "LoRaWanMinimal_APP.h"
#include "Arduino.h"
//14mA en actif - 10mA en veille
// Pb Battery : 0.7A
//LowPower -  32uA
// MOSFET IRF520 de Velleman

#define PIN_TRANSISTOR GPIO4

//CLEFS A MODIFIER SELON TTN
const char* APP_EUI = "2025435102035120";                     
const char* DEV_EUI = "1651321365432120";                     
const char* APP_Key = "13513216543213543213543543212135";  

int temps = 120; // Indiquez dans cette ligne la fréquence d'envoi de données, en secondes. (Ne pas aller plus bas que 3minutes, soit 180sec)

uint16_t userChannelsMask[6]={ 0x00FF,0x0000,0x0000,0x0000,0x0000,0x0000 };
static uint8_t counter=0;
uint8_t lora_data[1];
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

  
  pinMode(PIN_TRANSISTOR,OUTPUT);
  digitalWrite(PIN_TRANSISTOR,LOW);
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
  
  Serial.printf("\nVoltage : %d\n", voltage);
  lora_data[0] = voltage;

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

//Example of handling downlink data
void downLinkDataHandle(McpsIndication_t *mcpsIndication)
{
  Serial.printf("Received downlink: %s, RXSIZE %d, PORT %d, DATA: ",mcpsIndication->RxSlot?"RXWIN2":"RXWIN1",mcpsIndication->BufferSize,mcpsIndication->Port);
  for(uint8_t i=0;i<mcpsIndication->BufferSize;i++) {
    Serial.printf("%02X",mcpsIndication->Buffer[i]);
  }
  Serial.println();
  
  downlink = mcpsIndication->Buffer[0];
  Serial.println();
  if (downlink == 1){
    Serial.println("active downlink received");
    digitalWrite(PIN_TRANSISTOR,HIGH);
    delay(5000);
    digitalWrite(PIN_TRANSISTOR,LOW);

  }
  else {Serial.println("passive donwlink received");}  
}
