
#include <lmic.h>
#include <hal/hal.h>
#include <SPI.h>
#include <avr/sleep.h> 

#define TTN_APPEUI { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } // TTN Application EUI with "lsb"
#define TTN_DEVEUI { 0x00, 0xC2, 0x04, 0xD0, 0x7E, 0xD5, 0xB3, 0x70 } // TTN Device EUI with "lsb"
#define TTN_APPKEY { 0x76, 0x98, 0x31, 0x99, 0x41, 0xC9, 0xA7, 0xE6, 0x20, 0xC3, 0xD9, 0x9A, 0xA8, 0xCD, 0x54, 0xEA } // TTN App Key with "msb"

static const u1_t PROGMEM APPEUI[8]=TTN_APPEUI;
void os_getArtEui (u1_t* buf) { memcpy_P(buf, APPEUI, 8);}
static const u1_t PROGMEM DEVEUI[8]=TTN_DEVEUI;
void os_getDevEui (u1_t* buf) { memcpy_P(buf, DEVEUI, 8);}
static const u1_t PROGMEM APPKEY[16] = TTN_APPKEY;
void os_getDevKey (u1_t* buf) {  memcpy_P(buf, APPKEY, 16);}

static uint8_t LORA_DATA[2];
static osjob_t sendjob;
const unsigned TX_INTERVAL = 250;

// PIN definition for module
#define PIN_LMIC_NSS  10
#define PIN_LMIC_RST  A0
#define PIN_LMIC_DIO0 5
#define PIN_LMIC_DIO1 6
#define PIN_LMIC_DIO2 7

volatile int POWER_DOWN_SLEEP_COUNTER = 0;
bool GO_DEEP_SLEEP = false;

// Pin mapping
const lmic_pinmap lmic_pins = {
    .nss = PIN_LMIC_NSS,
    .rxtx = LMIC_UNUSED_PIN,
    .rst = PIN_LMIC_RST,
    .dio = {PIN_LMIC_DIO0, PIN_LMIC_DIO1, PIN_LMIC_DIO2},
};


void setup() {
    Serial.begin(115200);
    Serial.println("setup");
    PrintResetReason();
    LoRaWANVersion();
    delay(3000);
    PowerDownSetupWatchdog();
    LoRaWANSetup();
    Serial.println(F("Starting"));
    //LoRaWANDo_send(&sendjob);
    pinMode(2,OUTPUT);
}

void loop() {
    if (GO_DEEP_SLEEP == true)
    {
        PowerDownTXIntervall();
        GO_DEEP_SLEEP = false;
    }
    else
    {
        os_runloop_once();
    }
}

void printHex2(unsigned v) {
    v &= 0xff;
    if (v < 16)
        Serial.print('0');
    Serial.print(v, HEX);
}

void onEvent(ev_t ev)
{
    Serial.print(os_getTime());
    Serial.print(": ");
    switch (ev)
    {
    case EV_SCAN_TIMEOUT:
        Serial.println(F("EV_SCAN_TIMEOUT"));
        break;
    case EV_BEACON_FOUND:
        Serial.println(F("EV_BEACON_FOUND"));
        break;
    case EV_BEACON_MISSED:
        Serial.println(F("EV_BEACON_MISSED"));
        break;
    case EV_BEACON_TRACKED:
        Serial.println(F("EV_BEACON_TRACKED"));
        break;
    case EV_JOINING:
        Serial.println(F("EV_JOINING"));
        break;
    case EV_JOINED:
        Serial.println(F("EV_JOINED"));
#ifndef DISABLE_JOIN
        {
            u4_t netid = 0;
            devaddr_t devaddr = 0;
            u1_t nwkKey[16];
            u1_t artKey[16];
            LMIC_getSessionKeys(&netid, &devaddr, nwkKey, artKey);
            Serial.print("netid: ");
            Serial.println(netid, DEC);
            Serial.print("devaddr: ");
            Serial.println(devaddr, HEX);
            Serial.print("artKey: ");
            for (size_t i = 0; i < sizeof(artKey); ++i)
            {
                Serial.print(artKey[i], HEX);
            }
            Serial.println("");
            Serial.print("nwkKey: ");
            for (size_t i = 0; i < sizeof(nwkKey); ++i)
            {
                Serial.print(nwkKey[i], HEX);
            }
            Serial.println("");
        }
        LMIC_setLinkCheckMode(0);
        LMIC_setDrTxpow(DR_SF7,14);
        LMIC_setAdrMode(1); 
#endif
        break;
    /*
        || This event is defined but not used in the code. No
        || point in wasting codespace on it.
        ||
        || case EV_SCAN_FOUND:
        ||    Serial.println(F("EV_SCAN_FOUND"));
        ||    break;
        */
    case EV_JOIN_FAILED:
        Serial.println(F("EV_JOIN_FAILED"));
        break;
    case EV_REJOIN_FAILED:
        Serial.println(F("EV_REJOIN_FAILED"));
        break;
    case EV_TXCOMPLETE:
        Serial.println(F("EV_TXCOMPLETE"));

        if (LMIC.txrxFlags & TXRX_ACK)
        {
            Serial.println(F("Received ack"));
        }

        if (LMIC.dataLen)
        {
            Serial.print(LMIC.dataLen);
            Serial.println(F(" bytes of payload"));
        }

        // Schedule next transmission
        os_setTimedCallback(&sendjob, os_getTime() + sec2osticks(TX_INTERVAL), LoRaWANDo_send);
        GO_DEEP_SLEEP = true;

        break;
    case EV_LOST_TSYNC:
        Serial.println(F("EV_LOST_TSYNC"));
        break;
    case EV_RESET:
        Serial.println(F("EV_RESET"));
        break;
    case EV_RXCOMPLETE:
        // data received in ping slot
        Serial.println(F("EV_RXCOMPLETE"));
        break;
    case EV_LINK_DEAD:
        Serial.println(F("EV_LINK_DEAD"));
        break;
    case EV_LINK_ALIVE:
        Serial.println(F("EV_LINK_ALIVE"));
        break;
    /* This event is defined but not used in the code.
        case EV_SCAN_FOUND:
            DisplayPrintln(F("EV_SCAN_FOUND"), LORAWAN_STATE_DISPLAY_LINE);
            break;
        */
    case EV_TXSTART:
        Serial.println(F("EV_TXSTART"));
        break;
    case EV_TXCANCELED:
        Serial.println(F("EV_TXCANCELED"));
        break;
    case EV_RXSTART:
        /* do not print anything -- it wrecks timing */
        break;
    case EV_JOIN_TXCOMPLETE:
        Serial.println(F("EV_JOIN_TXCOMPLETE: no JoinAccept"));
        break;
    default:
        Serial.print(F("Unknown event: "));
        Serial.println((unsigned)ev);
        break;
    }
}

void do_send(osjob_t* j){
    // Check if there is not a current TX/RX job running
    if (LMIC.opmode & OP_TXRXPEND) {
        Serial.println(F("OP_TXRXPEND, not sending"));
    } else {
        // Prepare upstream data transmission at the next possible time.
        LMIC_setTxData2(1, LORA_DATA, sizeof(LORA_DATA)-1, 0);
        Serial.println(F("Packet queued"));
    }
    // Next TX is scheduled after TX_COMPLETE event.
}





void PrintResetReason()
{
  uint8_t mcusr_copy = MCUSR;
  MCUSR = 0;
  Serial.print("MCUSR:");
  if(mcusr_copy & (1<<WDRF)) Serial.print(" WDRF");
  if(mcusr_copy & (1<<BORF)) Serial.print(" BORF");
  if(mcusr_copy & (1<<EXTRF)) Serial.print(" EXTRF");
  if(mcusr_copy & (1<<PORF)) Serial.print(" PORF");
  Serial.println();
}

void LoRaWANVersion()
{
    Serial.print(F("LMIC: "));
    Serial.print(ARDUINO_LMIC_VERSION_GET_MAJOR(ARDUINO_LMIC_VERSION));
    Serial.print(F("."));
    Serial.print(ARDUINO_LMIC_VERSION_GET_MINOR(ARDUINO_LMIC_VERSION));
    Serial.print(F("."));
    Serial.print(ARDUINO_LMIC_VERSION_GET_PATCH(ARDUINO_LMIC_VERSION));
    Serial.print(F("."));
    Serial.println(ARDUINO_LMIC_VERSION_GET_LOCAL(ARDUINO_LMIC_VERSION));
}

void PowerDownSetupWatchdog()
{
  cli(); // Disable global interrupts
  MCUSR &= ~(1<<WDRF); // Clear WDRF: Watchdog Reset Flag
  WDTCSR |= (1<<WDCE) | (1<<WDE); // WDCE: Watchdog Change Enable, WDE: Watchdog System Reset Enable

  // Watchdog Timer Prescaler
  //WDTCSR = (1<<WDP2) | (1<<WDP0);             // 0.5 seconds
  //WDTCSR = (1<<WDP2) | (1<<WDP1);             // 1.0 seconds
  //WDTCSR = (1<<WDP2) | (1<<WDP1) | (1<<WDP0); // 2.0 seconds
  //WDTCSR = (1<<WDP3);                         // 4.0 seconds
  WDTCSR = (1<<WDP3) | (1<<WDP0);             // 8.0 seconds

  sei(); // Enable global interrupts
}

void PowerDownTXIntervall()
{
    int sleep_cycles = TX_INTERVAL / 8;
    Serial.println(F("PowerDown..."));
    Serial.println(sleep_cycles);

    Serial.flush();        

    for (int i=0; i<=sleep_cycles+1; i++) 
    {
      PowerDownUpdateMicros();
    }

    Serial.println(F("PowerUp..."));
}

void PowerDown()
{
  ADCSRA &= ~(1<<ADEN);                 // ADC Disable for power saving
  
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);  // Use the Power Down sleep mode
  cli();                                // Disable interrupts
  WDTCSR |= (1<<WDIE);                  // WDTIE: Watchdog Timer Interrupt Enable
  sleep_enable();                       // Sets the Sleep Enable bit in the MCUCR Register (SE BIT)
  sleep_bod_disable();                  // Disable Brown-Out Detection
  sei();                                // Enable interrupts
  sleep_mode();                         // go to sleep and wait for interrupt...
  sleep_disable();                      // Clear SE bit
  WDTCSR &= ~(1<<WDIE);                 // WDTIE: Watchdog Timer Interrupt Disable
  sei();                                // Enable interrupts

  ADCSRA |= (1<<ADEN);                  // ADC Enable
}

void PowerDownUpdateMicros()
{
    extern volatile unsigned long timer0_overflow_count;
    PowerDown();
    cli();
    // LMIC uses micros() to keep track of the duty cycle, so
    // hack timer0_overflow for a rude adjustment:  
    timer0_overflow_count+= 8 * 64 * clockCyclesPerMicrosecond();
    sei();
}

void LoRaWANSetup()
{
    Serial.println(F("LoRaWAN_Setup ..."));

    // LMIC init
    os_init();

    // Reset the MAC state. Session and pending data transfers will be discarded.
    LMIC_reset();

    // Let LMIC compensate for +/- 1% clock error
    LMIC_setClockError(MAX_CLOCK_ERROR * 1 / 100);

    // Start job
    LoRaWANDo_send(&sendjob);
}

void LoRaWANDo_send(osjob_t *j)
{
    // Check if there is not a current TX/RX job running
    if (LMIC.opmode & OP_TXRXPEND)
    {
        Serial.println(F("OP_TXRXPEND, not sending"));
    }
    else
    {
        LoRaWANGetData();

        // Prepare upstream data transmission at the next possible time.
        LMIC_setTxData2(1, LORA_DATA, sizeof(LORA_DATA), 0);
        Serial.println(F("Packet queued"));
    }
    // Next TX is scheduled after TX_COMPLETE event.
}
ISR(WDT_vect)
{
    POWER_DOWN_SLEEP_COUNTER ++;
}

void LoRaWANGetData()
{
    digitalWrite(2,HIGH);
    delay(500);
    int value2 = analogRead(A2)/4;
    digitalWrite(2,LOW);
    Serial.print('Val1 : ');
    Serial.println(value2);
    LORA_DATA[0] = value2;
    
    digitalWrite(3,HIGH);
    delay(500);
    int value3 = analogRead(A3)/4;
    digitalWrite(3,LOW);
    Serial.print('Val2 : ');
    Serial.println(value3);
    LORA_DATA[1] = value3;
}
