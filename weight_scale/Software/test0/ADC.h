#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>

#define MCP3462_OSR 0b0011 //64     Use OSR>=20480 to get 50Hz rejection
#define MCP3462_AMCLK_PSC 0b00 // No divide
#define MCP3462_GAIN //Max analog gain is 16

#define SPI_CS_PORT PORTB
#define SPI_CS_PIN PINB0
#define SPI_CS_DDR DDRB


//CMD frame: 2 device addr bits / 4 reg addr bits / 2 cmd type bits
#define SPI_ADDR 0b01000000
#define SPI_TYPE_STATIC_R 0b00000001
#define SPI_TYPE_INC_R 0b00000011
#define SPI_TYPE_INC_W 0b00000010

#define REG_ADCDATA 0x00
//status byte 0b00010abc
//a=data ready (active low)
//b=CRC error (active low)
//c=POR (active low)

class MCP3462 {
    public:
        MCP3462(void);
        ~MCP3462(void);
        bool isDataReady(void);
        uint32_t getDirectData(void);
        uint32_t getGainedData(void);
    private:
        uint8_t readByte(uint8_t addr);
        uint8_t writeByte(uint8_t addr);
        uint8_t transmit(uint8_t d);
};


#endif
