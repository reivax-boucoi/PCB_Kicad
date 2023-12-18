#include "Accelero.h"

#include <Wire.h>
#include "i2c.h"
#include "i2c_MMA8451.h"

MMA8451 mma8451;

ACC::ACC(uint8_t rate, uint8_t gees) {
    if (!mma8451.initialize(rate, gees))
        Serial.println("Accelerometer not detected");
}
int16_t ACC::getY() {
    uint8_t _buf[2];
    i2c.read(0x1C, 0x03, _buf, 2);//0x1=X axis, 0x3=Y axis
    int16_t value = (_buf[0] << 6) | ((_buf[1] >> 2) & 0x63);
    if (value > 8191) value -= 16384;
    meanY = (7 * meanY + value) >> 3;
    maxY = max(value, maxY - 1);
    minY = min(value, minY + 1);

    //float acc=float(accA)/4096.0;//4096=2g range, 1024=8g range
    /*  acc_min=min(accA,acc_min+10);
        acc_max=max(accA,acc_max-10);

        Serial.print(acc_max);
        Serial.print(',');
        Serial.print(acc_min);
        Serial.print(',');
        Serial.println(accA);*/
    return value;
}

void ACC::print() {
    Serial.print(meanY);
    Serial.print(',');
    Serial.print(maxY);
    Serial.print(',');
    Serial.print(minY);
    Serial.print(',');
    Serial.println(value);
}
