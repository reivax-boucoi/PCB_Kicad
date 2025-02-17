#ifndef M590_h
#define M590_h

#include <Arduino.h>
#include <EEPROM.h>  // Include EEPROM library

#define COMMAND_TIMEOUT 1000
#define ASYNC_TIMEOUT   20000
#define STATUS_POLLING_RATE 250

#define SMS_TIMEOUT 10000
#define SW_RETRY_CNT 10
#define EEPROM_NUMBER_ADDR 40  // EEPROM address to store target phone number
#define EEPROM_SIMPIN_ADDR 60  // EEPROM address to store SIM pin #

enum m590ResponseCode {
    M590_SUCCESS,
    M590_FAILURE,
    M590_TIMEOUT,
    M590_LENGTH_EXCEEDED,
    M590_ASYNC_RUNNING,
    M590_NO_PARAMETERS,
    M590_UNDEFINED
};

enum m590States {
    M590_STATE_SHUTDOWN,                        //0
    M590_STATE_STARTUP,
    M590_STATE_STARTUP_DONE,
    M590_STATE_PIN_REQUIRED,
    M590_STATE_PIN_ENTRY_DONE,
    M590_STATE_PIN_VALIDATION,                  //5
    M590_STATE_PIN_VALIDATION_DONE,
    M590_STATE_CELLULAR_CONNECTING,
    M590_STATE_CELLULAR_CONNECTED,
    M590_STATE_INPUT_MODE,
    M590_STATE_INPUT_MODE_DONE,
    M590_STATE_FATAL_ERROR                      //11
};

enum m590NetworkStates {
    M590_NET_NOT_REGISTERED_NOT_SEARCHING,
    M590_NET_REGISTERED,
    M590_NET_REGISTRATION_REFUSED,
    M590_NET_SEARCHING_NOT_REGISTERED,
    M590_NET_UNKNOWN,
    M590_NET_REGISTERED_ROAMING,
    M590_NET_PARSE_ERROR, //not actually part of response, used to determine function failure
};

class M590 {
    public:
        M590(char *text_ptr );
        bool begin(unsigned long baudRate = 115200, HardwareSerial *gsmSerial = NULL);
        void enableDebugSerial(HardwareSerial *debugSerial = NULL);
        int available();
        char read();
        void write(const char c);
        void print(String s);
        bool initialize(String pin = "");
        void loop();
        bool checkAlive(void(*callback)(void) = NULL);
        bool checkPinRequired();
        bool sendPinEntry(String pin, void(*callback)(void) = NULL);
        m590NetworkStates checkNetworkState();
        bool waitForRegistration(const unsigned int timeout);

        bool queueSMS();
        String targetNum="0605006547";
        void setTargetNum(String num);//Update target phone number and store into eeprom
        String SIMPIN="0000";
        void setSIMPin(String pin);//Update SIM pin and store into eeprom
        bool reInit();
        uint8_t newSMSAvailable();
        String getSMS();
        char *_text_ptr=NULL;

    private:
        HardwareSerial *_gsmSerial;
        HardwareSerial *_debugSerial;
        m590States _currentState = M590_STATE_SHUTDOWN;
        m590States _previousState = M590_STATE_SHUTDOWN;
        unsigned long _asyncStartTime = 0;
        byte _asyncBytesMatched = 0;
        byte _asyncResponseLength = 0;
        const char *_asyncProgmemResponseString = NULL;
        char _responseBuffer[16];

        uint8_t restartRetries=0;
        
        byte asyncMatchedChars = 0;
        void sendCommandWithoutPrefix(const char *progmemCommand,const char *params = NULL);
        void sendCommand(const char *progmemCommand,const char *params = NULL);
        void resetAsyncVariables();
        m590ResponseCode readForAsyncResponse(const char *progmemResponseString = NULL,const unsigned int timeout = ASYNC_TIMEOUT);
        //if given a buffer pointer, the buffer will contain the response data after the colon
        m590ResponseCode readForResponse(const char *progmemResponseString,char *buffer = NULL,const unsigned int max_bytes = 0,const unsigned int timeout = COMMAND_TIMEOUT);
        m590ResponseCode readForResponses(const char *progmemResponseString,const char *progmemFailString,const unsigned int timeout = COMMAND_TIMEOUT);
        m590ResponseCode serialToBuffer(char *buffer,const char readUntil,const unsigned int max_bytes,const unsigned int timeout = COMMAND_TIMEOUT);
        m590ResponseCode readUntil(const char readUntil,const unsigned int timeout = COMMAND_TIMEOUT);
        bool bufferStartsWithProgmem(char *buffer,const char *progmemString);
        void printDebug(const char *progmemString, bool withNewline = true);
        void printDebug(const String s, bool withNewline = true);
};

#endif

/*  void _handleReturn(String retStr); //handle an async answer from the module
     void _parseReturn(char c);

     void _parseSerial();*/


/*  void loop(); //function called on every loop
    //void begin(String pin); //connect to cellular network with pin
    byte getSignalStrength(); //return current signal strength
    void beginGPRS(String apn); //connect data link with APN
    void beginGPRS(String apn, String user, String pass); //connect data link with APN login credentials
    bool connectTCP(String ip, String port); //initialize TCP connection, returns success
    bool disconnectTCP(); //disconnect TCP connection
    String doRequest(String req); //perform an HTTP request
    String dns(String host); //perform a DNS request
    bool sendAT(String cmd); //send an AT command directly to the M590 module*/
