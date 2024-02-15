#define IR_SMALLD_RC5
#include <IRsmallDecoder.h>

#define IR_PIN 7
IRsmallDecoder irDecoder(IR_PIN);
irSmallD_t irData;
void setup() {
    Serial.begin(115200);
    while (!Serial) {
        ; // wait for serial port to connect. Needed for native USB port only
    }
    Serial.println("Hello !");
}

void loop() {
    if (irDecoder.dataAvailable(irData)) {
        Serial.print(irData.addr, HEX);
        Serial.print("\t ");
        Serial.println(irData.cmd, HEX);

        if (irData.addr == 0x0) {
            switch (irData.cmd) {
                case 0x10:
                case 0x11:
                case 0x20:
                case 0x21:
                case 0x0D:
//                    myAnimations.setAnim(irData.cmd);
                    Serial.print("IR code: ");
                    Serial.println(irData.cmd,HEX);
                    break;
                    
                case 0xC: //ON/OFF
                    Serial.println("IR remote turn OFF !");
                    break;
                default:
                    Serial.println("Unknwown IR remote codeat addr 0");
            }

        }else{
                    Serial.print("Unknwown IR remote addr ");
                    Serial.println(irData.addr);
            
        }
    }
}
