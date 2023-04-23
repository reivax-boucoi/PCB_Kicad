#ifndef SCL_H_
#define SCL_H_

#include <avr/io.h>
#include "ADC.h"
#include "UART.h"

class Scale{
public:
    Scale(UART* u);
    ~Scale(void);
    int32_t gain;
    int32_t offset;
    int32_t value;
    int32_t value_scl;
    int32_t getWeight(void);
    int32_t tare(void);
    void showWeight(bool verbose);
    
private:
    MCP3462 myADC;
    UART *uart;
    
};

#endif
