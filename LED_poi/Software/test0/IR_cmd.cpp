#include "IR_cmd.h"
#include "utils.h"
#include <IRsmallDecoder.h>

//numbers: 0x10 //Numbers 1-6 correspond to addr=0x10 and cmd 0-5
//ON/OFF=10 15
//VOL+ 10 12, VOL- 10 13
//OK 1A 7C, back 1a 7d
//up 1a 78, right 1a 7b, down 1a 79, left 1a 7a
// play 1a 32, stop 1a 38, pause 1a 39, p+ 1a 31, p- 1a 30, t- 1a 33, t+ 1a 34
//clear 1a 0f

IRsmallDecoder irDecoder(IR_PIN);
irSmallD_t irData;



void IR_poll() {
    if (irDecoder.dataAvailable(irData)) {
        Serial.print(irData.addr, HEX);
        Serial.print("\t ");
        Serial.println(irData.cmd, HEX);

        if (irData.addr == 0x10) {
            switch (irData.cmd) {
                case 0x00:
                case 0x01:
                case 0x02:
                case 0x03:
                case 0x04:
                case 0x05:
//                    myAnimations.setAnim(irData.cmd);
                    break;
                    
                case 0x15: //ON/OFF
                    supply_OFF();
                    break;
                default:
                    Serial.println("Unknwown code");
            }

        }
    }
}
