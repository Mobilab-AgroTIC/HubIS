#include "LowPower.h"

#define TRANSISTOR A0
#define STEPPER_PIN_1 10
#define STEPPER_PIN_2 11
#define STEPPER_PIN_3 12
#define STEPPER_PIN_4 13
int step_number = 0;
const int wakeUpPin = 2;

void wakeUp()
{
    // Just a handler for the pin interrupt.
}


void setup() {
  Serial.begin(115200);
  pinMode(STEPPER_PIN_1, OUTPUT);
  pinMode(STEPPER_PIN_2, OUTPUT);
  pinMode(STEPPER_PIN_3, OUTPUT);
  pinMode(STEPPER_PIN_4, OUTPUT);
  pinMode(TRANSISTOR,OUTPUT);
  pinMode(wakeUpPin, INPUT);   
  shutDownStepper();
}

void loop() {

  delay(10);
  shutDownStepper();
  delay(10);
  deepSleep();
  
  Serial.println("----LOOP----");
  if (digitalRead(2)==1){
    Serial.println("----Wake Up----");
    digitalWrite(TRANSISTOR,HIGH);
    Serial.println("sens 1");
    for (int i = 0; i <= 512; i++) {
      OneStep(false);
      delay(10);
    }
    delay(1000);
    Serial.println("sens 2");
    for (int i = 0; i <= 512; i++) {
      OneStep(true);
      delay(10);
    }    
  }
  Serial.println("----LOOP END----");

}


void OneStep(bool dir){
  if(dir){
    switch(step_number){
      case 0:
        digitalWrite(STEPPER_PIN_1, HIGH);
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, LOW);
      break;
      case 1:
        digitalWrite(STEPPER_PIN_1, LOW);
        digitalWrite(STEPPER_PIN_2, HIGH);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, LOW);
      break;
      case 2:
        digitalWrite(STEPPER_PIN_1, LOW);
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, HIGH);
        digitalWrite(STEPPER_PIN_4, LOW);
        break;
      case 3:
        digitalWrite(STEPPER_PIN_1, LOW);
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, HIGH);
        break;
    } 
  }
  else{
    switch(step_number){
      case 0:
        digitalWrite(STEPPER_PIN_1, LOW);
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, HIGH);
        break;
      case 1:
        digitalWrite(STEPPER_PIN_1, LOW);
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, HIGH);
        digitalWrite(STEPPER_PIN_4, LOW);
        break;
      case 2:
        digitalWrite(STEPPER_PIN_1, LOW);
        digitalWrite(STEPPER_PIN_2, HIGH);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, LOW);
        break;
      case 3:
        digitalWrite(STEPPER_PIN_1, HIGH);
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, LOW);
    } 
  }
  
step_number++;
if(step_number > 3){
  step_number = 0;
  }
}

void shutDownStepper() {
  digitalWrite(TRANSISTOR,LOW);
  digitalWrite(STEPPER_PIN_1, LOW);
  digitalWrite(STEPPER_PIN_2, LOW);
  digitalWrite(STEPPER_PIN_3, LOW);
  digitalWrite(STEPPER_PIN_4, LOW);  
}

void deepSleep() {
  attachInterrupt(0, wakeUp, RISING);
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF); 
  detachInterrupt(0);
}
