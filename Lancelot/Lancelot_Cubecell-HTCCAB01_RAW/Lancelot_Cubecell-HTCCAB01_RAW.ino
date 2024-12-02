#include "LoRaWanMinimal_APP.h"
#include "Arduino.h"

//Set these OTAA parameters to match your app/node in TTN
uint8_t devEui[] = { 0x70, 0xB3, 0xD5, 0x7E, 0xD0, 0x05, 0x68, 0xA3 };
uint8_t appEui[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
uint8_t appKey[] = { 0x8D, 0x77, 0xA2, 0x41, 0xAA, 0x33, 0xDC, 0x20, 0x68, 0x2A, 0xD9, 0x48, 0x68, 0x69, 0xA8, 0x4B };
int temps = 180; // Indiquez dans cette ligne la fréquence d'envoi de données, en secondes. (Ne pas aller plus bas que 3minutes, soit 180sec)

uint16_t userChannelsMask[6]={ 0x00FF,0x0000,0x0000,0x0000,0x0000,0x0000 };
static uint8_t counter=0;
uint8_t lora_data[1];
uint8_t downlink ;

//Some utilities for going into low power mode
TimerEvent_t sleepTimer;
//Records whether our sleep/low power timer expired
bool sleepTimerExpired;


//declare variables for the motor pins
int motorPin1 = GPIO1;    // Blue   - 28BYJ48 pin 1
int motorPin2 = GPIO2;    // Pink   - 28BYJ48 pin 2
int motorPin3 = GPIO3;    // Yellow - 28BYJ48 pin 3
int motorPin4 = GPIO4;    // Orange - 28BYJ48 pin 4
                          // Red    - 28BYJ48 pin 5 (VCC)

int motorSpeed = 1200;  //variable to set stepper speed
int count = 0;          // count of steps made
int countsperrev = 512; // number of steps per full revolution
int lookup[8] = {B1000, B1100, B0100, B0110, B0010, B0011, B0001, B1001};

//////////////////////////////////////////////////////////////////////////////
void setup() {
  //declare the motor pins as outputs
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4,LOW);

  Serial.begin(115200);
  
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

//////////////////////////////////////////////////////////////////////////////
void loop(){
  counter++; 
  delay(10);
  uint8_t voltage = getBatteryVoltage()/50; //Tension en %

  Serial.printf("\nHello ! Voltage : %d\n", voltage);
  lora_data[0] = voltage;
  
  //Now send the data. The parameters are "data size, data pointer, port, request ack"
  Serial.printf("\nSending packet with counter=%d\n", counter);
  Serial.printf("\nValue to send : %d\n", lora_data[1]);

  //Here we send confirmed packed (ACK requested) only for the first five (remember there is a fair use policy)
  bool requestack=counter<2?true:false;
  if (LoRaWAN.send(sizeof(lora_data), lora_data, 1, requestack)) {
    Serial.println("Send OK");
  } else {
    Serial.println("Send FAILED");
  }

  lowPowerSleep(temps*1000);  
  delay(10);
  

}

//////////////////////////////////////////////////////////////////////////////

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
    while ( count < countsperrev / 4 ) {
      anticlockwise();
      count++;
      }
    while ( count < countsperrev / 2 ) {
      clockwise();
      count++;
      }
    count = 0;
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
    digitalWrite(motorPin3, LOW);
    digitalWrite(motorPin4,LOW);
    delay(10);
  }
  else {Serial.println("passive donwlink received");}  
}

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

//////////////////////////////////////////////////////////////////////////////

void anticlockwise()
{
  for(int i = 0; i < 8; i++)
  {
    setOutput(i);
    delayMicroseconds(motorSpeed);
  }
}

void clockwise()
{
  for(int i = 7; i >= 0; i--)
  {
    setOutput(i);
    delayMicroseconds(motorSpeed);
  }
}

void setOutput(int out)
{
  digitalWrite(motorPin1, bitRead(lookup[out], 0));
  digitalWrite(motorPin2, bitRead(lookup[out], 1));
  digitalWrite(motorPin3, bitRead(lookup[out], 2));
  digitalWrite(motorPin4, bitRead(lookup[out], 3));
}
