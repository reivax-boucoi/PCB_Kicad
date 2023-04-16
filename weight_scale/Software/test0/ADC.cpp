#include "ADC.h"


MCP3462::MCP3462(void){
    
    DDRB=0b00000110;//set SCK, MOSI to outputs, MISO to input
    SPI_CS_DDR |=(1<<SPI_CS_PIN); //set CSB pin as output
    SPI_CS_PORT |=(1<<SPI_CS_PIN); //set CSB initial state to high
    SPCR = (1<<SPE)|(1<<MSTR);

    //set COMMAND to write incremental
    //W CONFIG0 (0x1): 0b11100011 //sets clock to internal, no current source/sink/ADC in conversion mode
    //W CONFIG1 (0x2): (MCP3462_AMCLK_PSC<<6) | (MCP3462_OSR<<2);
    //W CONFIG2 (0x3): (0b10<<6)|(MCP3462_GAIN<<3)|0b111;   //BBOST current x1, Gain, AutoZero enabled
    //W CONFIG3: 0b11xx0000 Continuous conversion, no CRC, offset or gain cal. 
        //XX is data format: 00=16 signed bits. 11=32bits total: 4 bits chan ID + 12x sign bit + 16bits data
    
    //TODO: read OFFSET (MUX 0x88) and write opposite into OFFSETCAL. May not be necessary if AutoZero is enabled
    /*
    Enable SCAN mode: 
    raw input: CH0-CH1: bit 8, MUX 0x01
    gained input: CH2-CH3: bit 9, MUX 0x23
    TEMP: 12, MUX 0xDE. Equation: 0.00133*ADC-267.146
    AVdd: 13, scale factor 1/3, MUX 0x98->may not be relevant sinc erelative to ref+/-
    
    Scan DLY: between adc mux change:   111=512 DMclock periods
                                        000=0clock periods
        TIMER[23:0]: 0->0n  24 '1'->16777215 periods
    */
}
MCP3462::~MCP3462(void){
    
}

bool MCP3462::isDataReady(void){
    return 0;
}

uint32_t MCP3462::getDirectData(void){
    return 0;
}

uint32_t MCP3462::getGainedData(void){
    return 0;
}
/*
uint32_t MCP3462::readADCreg(void){
    uint32_t d=0
    SPI_CS_PORT &=~(1<<SPI_CS_PIN); //set CSB low
    uint8_t d=transmit(addr)
    SPI_CS_PORT |=(1<<SPI_CS_PIN); //set CSB high
    return d;
    
}
*/
uint8_t MCP3462::readByte(uint8_t addr){
    SPI_CS_PORT &=~(1<<SPI_CS_PIN); //set CSB low
    uint8_t d=transmit(addr);
    SPI_CS_PORT |=(1<<SPI_CS_PIN); //set CSB high
    return d;
}

uint8_t MCP3462::writeByte(uint8_t addr){
    SPI_CS_PORT &=~(1<<SPI_CS_PIN); //set CSB low
    
    
    SPI_CS_PORT |=(1<<SPI_CS_PIN); //set CSB high
    return 0;
    
}
uint8_t MCP3462::transmit(uint8_t d){
    SPDR = d;
    while(!(SPSR & (1<<SPIF)));
    return SPDR;
}
