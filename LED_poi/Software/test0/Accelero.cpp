#include "Accelero.h"

#include <Wire.h>
#include "i2c.h"

#define ADXL343_ADDRESS (0x53) //ALT adress pin LOW, A6 for write, A7 for read

#define ADXL3XX_DEVID (0xE5)           /**< Device ID, located at reg ADXL3XX_REG_DEVID */
#define ADXL3XX_REG_DEVID (0x00)       /**< Device ID,*/
#define ADXL3XX_REG_BW_RATE (0x2C)     /**< Data rate and power mode control */
#define ADXL3XX_REG_POWER_CTL (0x2D)   /**< Power-saving features control */
#define ADXL3XX_REG_INT_ENABLE (0x2E)  /**< Interrupt enable control */
#define ADXL3XX_REG_INT_MAP (0x2F)     /**< Interrupt mapping control */
#define ADXL3XX_REG_INT_SOURCE (0x30)  /**< Source of interrupts */
#define ADXL3XX_REG_DATA_FORMAT (0x31) /**< Data format control */
#define ADXL3XX_REG_DATAX0 (0x32)      /**< X-axis data 0 */
#define ADXL3XX_REG_DATAX1 (0x33)      /**< X-axis data 1 */
#define ADXL3XX_REG_DATAY0 (0x34)      /**< Y-axis data 0 */
#define ADXL3XX_REG_DATAY1 (0x35)      /**< Y-axis data 1 */
#define ADXL3XX_REG_DATAZ0 (0x36)      /**< Z-axis data 0 */
#define ADXL3XX_REG_DATAZ1 (0x37)      /**< Z-axis data 1 */
#define ADXL3XX_REG_FIFO_CTL (0x38)    /**< FIFO control */
#define ADXL3XX_REG_FIFO_STATUS (0x39) /**< FIFO status */

//  ADXL343_DATARATE_400_HZ = 0b1100,  /**<  400Hz Bandwidth */
//  ADXL343_DATARATE_200_HZ = 0b1011,  /**<  200Hz Bandwidth */
//  ADXL343_DATARATE_100_HZ = 0b1010,  /**<  100Hz Bandwidth */
//  ADXL343_DATARATE_0_39_HZ = 0b0010, /**< 0.39Hz Bandwidth */
//  ADXL343_DATARATE_0_10_HZ = 0b0000, /**< 0.10Hz Bandwidth (default value) */
//  ADXL343_RANGE_16_G = 0b11, /**< +/- 16g */
//  ADXL343_RANGE_8_G = 0b10,  /**< +/- 8g */


ACC::ACC(uint8_t rate, uint8_t gees) {
    uint8_t _buf[2];
    i2c.read(ADXL343_ADDRESS, ADXL3XX_REG_DEVID, _buf, 1);
    if (_buf[0] != ADXL3XX_DEVID)
        Serial.println("Accelerometer not detected");
    return;

    i2c.read(ADXL343_ADDRESS, ADXL3XX_REG_DATAZ0, _buf, 2);
    int16_t value = (_buf[0] << 6) | ((_buf[1] >> 2) & 0x63);
    if (value > 8191) value -= 16384;
    maxY = value;
    minY = value;
    value_f = value;
    newHalfCycleFlag = false;
    cycleState = false;
    cntPos = 0;
    cntNeg = 0;
}
int16_t ACC::getY() {
    uint8_t _buf[2];
    i2c.read(ADXL343_ADDRESS, ADXL3XX_REG_DATAZ0, _buf, 2);
    int16_t value = (_buf[0] << 6) | ((_buf[1] >> 2) & 0x63);
    if (value > 8191) value -= 16384;


    value_f = (value_f * 3 + value) >> 2;
    maxY = max(value_f, maxY - ACC_DECAY);
    minY = min(value_f, minY + ACC_DECAY);

    cntPos++;
    cntNeg++;

    if (maxY == value_f && cycleState == false) {
        newHalfCycleFlag = true;
        cycleState = true;
        periodPos = cntPos;
        cntPos = 0;
    } else if (minY == value_f && cycleState == true) {
        newHalfCycleFlag = true;
        cycleState = false;
        periodNeg = cntNeg;
        cntNeg = 0;
    }

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

void ACC::printRaw() {
    Serial.print(value_f);
    Serial.print(',');
    Serial.print(maxY);
    Serial.print(',');
    Serial.print(minY);
    Serial.print(',');
    Serial.println(cycleState * 10000);
}

void ACC::printPeriod() {
    Serial.print(periodPos);
    Serial.print(',');
    Serial.print(periodNeg);
    Serial.print(',');
    Serial.print(cntPos);
    Serial.print(',');
    Serial.print(cntNeg);
    Serial.print(',');
    Serial.println(cycleState * 100);
}
