#include "ADC.h"


MCP3462::MCP3462(void){
    
    DDRB=0b00000110;//set SCK, MOSI to outputs, MISO to input
    PORTB=1;//MOSI, SCLK low, CSB high
    _delay_us(10);
    SPI_CS_DDR |=(1<<SPI_CS_PIN); //set CSB pin as output
    SPI_CS_PORT |=(1<<SPI_CS_PIN); //set CSB initial state to high
    SPCR = (1<<SPE)|(1<<MSTR);

    
    //TODO: read OFFSET (MUX 0x88) and write opposite into OFFSETCAL. May not be necessary if AutoZero is enabled
    /*
    Enable SCAN mode: 
    raw input: CH0-CH1: bit 8, MUX 0x01
    gained input: CH2-CH3: bit 9, MUX 0x23
    TEMP: 12, MUX 0xDE. Equation: 0.00133*ADC-267.146
    AVdd: 13, scale factor 1/3, MUX 0x98->may not be relevant since relative to ref+/-
    
    Scan DLY: between adc mux change:   111=512 DMclock periods
                                        000=0clock periods
        TIMER[23:0]: 0->0n  24 '1'->16777215 periods
    */
    
    //STATUS should be 0b00010111 111=Data Ready / CRC Status / POR Status
    //Active low: 0x16=POR, 0x17=OK, 0x13=Data ready
    
    SPI_CS_PORT &=~(1<<SPI_CS_PIN); //set CSB low
    transmit(SPI_ADDR|SPI_TYPE_INC_W|REG_CONFIG0);//Incremental write
    //W CONFIG0 (0x1): 0b11100011 //sets clock to internal, no current source/sink/ADC in conversion mode
    transmit(0b11100011);
    
    //W CONFIG1 (0x2): (MCP3462_AMCLK_PSC<<6) | (MCP3462_OSR<<2);
    transmit((MCP3462_AMCLK_PSC<<6) | (MCP3462_OSR<<2));
    
    //W CONFIG2 (0x3): (0b10<<6)|(MCP3462_GAIN<<3)|0b111;   //BBOST current x1, Gain, AutoZero enabled
    transmit((0b10<<6)|(MCP3462_GAIN<<3)|0b111);
    
    //W CONFIG3 (0x4): 0b11xx0000 Continuous conversion, no CRC, offset or gain cal. 
        //XX is data format: 00=16 signed bits. 11=32bits total: 4 bits chan ID + 12x sign bit + 16bits data
    transmit(0b11110000);
    
    //W IRQ (0x5): 0bxxxx0111 Interrupt output push pull enabled
    transmit(0b00000111);
    transmit(0b00000001);
    
    SPI_CS_PORT |=(1<<SPI_CS_PIN); //set CSB high
    _delay_ms(2);
}
MCP3462::~MCP3462(void){
    
}

bool MCP3462::isDataReady(void){
    return 0;
}

int32_t MCP3462::getDirectData(void){
    return readADCreg();
}

int32_t MCP3462::getGainedData(void){
    return 0;
}

int32_t MCP3462::readADCreg(void){
    uint8_t d=0;
    uint16_t ADC_code=0;
    uint32_t data=0;
    uint8_t ch=0;
    bool sign=false;
    SPI_CS_PORT &=~(1<<SPI_CS_PIN); //set CSB low
    
    uint8_t status=transmit(SPI_ADDR|SPI_TYPE_STATIC_R|REG_ADCDATA);
    if(status!=0x13)return 0xFFFFFFFF;//Data is not ready of other error (POR)
    
    d=transmit(0); //CH_ID[3:0], SIGN(4 bits)
    ch=d>>4;
    sign=d&0x01;
    data=d;
    
    d=transmit(0);//SIGN(8 bits)
    data=(data<<8)|d;
    
    d=transmit(0);//DATA[15:8]
    data=(data<<8)|d;
    ADC_code=d;
    
    d=transmit(0);//DATA[7:0]
    data=(data<<8)|d;
    ADC_code=(ADC_code<<8)|d;;
    
    SPI_CS_PORT |=(1<<SPI_CS_PIN); //set CSB high
    
    if(sign){
        return ((0x0000<<15) | ADC_code);        
    }else{
        return ((0x7000<<15) | ADC_code);
    }
    
}


uint8_t MCP3462::transmit(uint8_t d){
    SPDR = d;
    while(!(SPSR & (1<<SPIF)));
    return SPDR;
}
