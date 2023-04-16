#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>

#define MCP3462_OSR 64

class MCP3462 {
    public:
        MCP3462();
        ~MCP3462();
        static bool isDataReady(void);
        static uint32_t getDirectData(void);
        static uint32_t getGainedData(void);
        
};


#endif
