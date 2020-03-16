#include "mbed.h"
#include "sx1276-hal.h"
#include "radioevents.h"
#include "defines.h"

DigitalOut ledR(TALLY_LED_R);
DigitalOut ledG(TALLY_LED_G);
DigitalOut ledB(TALLY_LED_B);
Serial serial(TALLY_SERIAL1_TX, TALLY_SERIAL1_RX);

static RadioEvents_t radioEvents;

SX1276MB1xAS radio( NULL, TALLY_MOSI, TALLY_MISO, TALLY_SCLK, TALLY_NSS,
                    TALLY_RESET, TALLY_D0, TALLY_D1, TALLY_D2, TALLY_D3, 
                    TALLY_D4, TALLY_D5, TALLY_ANTSW);

int main()
{
    radioEvents.TxDone = OnTxDone;
    radioEvents.RxDone = OnRxDone;
    radioEvents.RxError = OnRxError;
    radioEvents.TxTimeout = OnTxTimeout;
    radioEvents.RxTimeout = OnRxTimeout;
    radio.Init( &radioEvents);

    serial.baud(19200);
    ledR = 1;

    uint8_t ver;
    while( (ver = radio.Read( REG_VERSION )) == 0x00  ) {
        serial.printf( "Radio could not be detected!\n\r");
        wait( 1 );
    }

    serial.printf( "Version %u!\n\r", ver);


    // All LEDs are OFF
    ledB = 1;
//    myled2 = 1;
//    myled3 = 1;

    while(1) {
        serial.printf("Hej");
        wait(1.0);
    }
}
