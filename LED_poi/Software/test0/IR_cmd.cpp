#include "IR_cmd.h"
#include "utils.h"

//Pinout: OUT GND VCC (similar to TSOP48xx)
//Library only works with pins 0 RXD, 1 TXD, 2 SDA, 3 SCL, 7 PE6
#define IR_SMALLD_RC5
#define IR_PIN 7

#include <IRsmallDecoder.h>


//Sony Hi-fi amp remote control:
//#define IR_SMALLD_SIRC12
//numbers: 0x10 //Numbers 1-6 correspond to addr=0x10 and cmd 0-5
//ON/OFF=10 15
//VOL+ 10 12, VOL- 10 13
//OK 1A 7C, back 1a 7d
//up 1a 78, right 1a 7b, down 1a 79, left 1a 7a
// play 1a 32, stop 1a 38, pause 1a 39, p+ 1a 31, p- 1a 30, t- 1a 33, t+ 1a 34
//clear 1a 0f

//Select1 junk remote: all addr is 0.
//#define IR_SMALLD_RC5
#define IR_KEY_CHUP  0x20
#define IR_KEY_CHDN  0x21
#define IR_KEY_VOLUP 0x10
#define IR_KEY_VOLDN 0x11
#define IR_KEY_MUTE  0x0D
#define IR_KEY_PWR   0x0C

IRsmallDecoder irDecoder(IR_PIN);
irSmallD_t irData;



void IR_poll() {
    if (irDecoder.dataAvailable(irData)) {

        if (irData.addr == 0x0) {
            Serial.print("IR remote ");
            switch (irData.cmd) {
                case IR_KEY_CHUP:
                    myAnimations->nextAnim(true);
                    break;
                case IR_KEY_CHDN:
                    myAnimations->nextAnim(false);
                    break;
                case IR_KEY_VOLUP:
                    if (++myAnimations->animSpeed == 0)myAnimations->animSpeed = 255;
                    Serial.print("set speed to ");
                    Serial.println(myAnimations->animSpeed);
                    break;
                case IR_KEY_VOLDN:
                    if (--myAnimations->animSpeed == 0)myAnimations->animSpeed = 1;
                    Serial.print("set speed to ");
                    Serial.println(myAnimations->animSpeed);
                    break;
                case IR_KEY_MUTE:
                    Serial.println(irData.cmd, HEX);
                    break;

                case IR_KEY_PWR:
                    supply_OFF();
                    break;
                default:
                    Serial.println("Unknwown IR remote codeat addr 0");
            }
        }/*else{
                    Serial.print("Unknwown IR remote addr ");
                    Serial.println(irData.addr);
        }*/
    }
}
