/*
    created March 2017
    by Leandro Späth
*/

#include <Arduino.h>
#include "M590.h"

const char M590_COMMAND_GET_SIM_IDENTIFICATION[]   PROGMEM = "CCID",
                                                   M590_COMMAND_CHECK_STATUS[]             PROGMEM = "CPAS",
                                                                                           M590_COMMAND_CHECK_NETWORK_STATUS[]     PROGMEM = "CREG?",
                                                                                                                                   M590_COMMAND_CHECK_PIN[]                PROGMEM = "CPIN?",
                                                                                                                                                                           M590_COMMAND_INPUT_PIN[]                PROGMEM = "CPIN=",
                                                                                                                                                                                                                   M590_COMMAND_SHUTDOWN[]                 PROGMEM = "CPWROFF",
                                                                                                                                                                                                                                                           M590_COMMAND_GET_SIGNAL_STRENGTH[]      PROGMEM = "CSQ",
                                                                                                                                                                                                                                                                                                   M590_COMMAND_GET_NATIVE_NUMBER[]        PROGMEM = "CNUM",
                                                                                                                                                                                                                                                                                                                                           M590_COMMAND_SET_INPUT_TEXT_MODE[]      PROGMEM = "CMGF=1",
                                                                                                                                                                                                                                                                                                                                                                                   M590_COMMAND_SET_INPUT_TEXT_FORMAT[]    PROGMEM = "CSCS=\"GSM\"",
                                                                                                                                                                                                                                                                                                                                                                                                                           M590_COMMAND_SEND_SMS[]                 PROGMEM = "CMGS=\"",
                                                                                                                                                                                                                                                                                                                                                                                                                                                                   M590_COMMAND_GET_SMS_CNT[]              PROGMEM = "CPMS?",
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           M590_COMMAND_GET_SMS_ATIDX[]            PROGMEM = "CMGR=1",
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   M590_COMMAND_DEL_SMS_ATIDX[]            PROGMEM = "CMGD=1";

const char
M590_RESPONSE_PREFIX[]          PROGMEM = "+",//"\r\n+",
                                M590_RESPONSE_SEPERATOR[]       PROGMEM = ": ",
                                                                M590_RESPONSE_OK[]              PROGMEM = "OK\r\n",
                                                                                                M590_RESPONSE_ERROR[]           PROGMEM = "ERROR\r\n",
                                                                                                                                M590_RESPONSE_FAIL[]            PROGMEM = "FAIL\r\n",
                                                                                                                                                                M590_RESPONSE_PIN_REQUIRED[]    PROGMEM = " SIM PIN",
                                                                                                                                                                                                M590_RESPONSE_PIN_DONE[]        PROGMEM = " READY",
                                                                                                                                                                                                                                M590_RESPONSE_PIN_VAL_DONE[]    PROGMEM = "+PBREADY";

const char
M590_AT[]                       PROGMEM = "AT",
                                M590_CRLF[]                     PROGMEM = "\r\n",
                                                                M590_COMMAND_PREFIX[]           PROGMEM = "AT+",
                                                                                                M590_CONTENT_LENGTH_HEADER[]    PROGMEM = "Content-Length: ";

const char
M590_ERROR_NOT_RESPONDING[]         PROGMEM = "\nThe M590 did not respond to an \"AT\". Please check serial connection, power supply and ONOFF pin.",
                                    M590_ERROR_NO_PIN[]                 PROGMEM = "\nNo pin was specified, but the module requests one",
                                                                        M590_ERROR_WRONG_PIN[]              PROGMEM = "\nWrong PIN was entered, down one try.",
                                                                                                            M590_ERROR_OTHER_PIN_ERR[]          PROGMEM = "\nError during PIN check, maybe a PUK is required, please check SIM card in a phone",
                                                                                                                                                M590_ERROR_PINVAL_TIMEOUT[]         PROGMEM = "\nTimeout during pin validation, please check module and try again",
                                                                                                                                                                                    M590_ERROR_UNHANDLED_NET_STATE[]    PROGMEM = "\nNetwork status returned unhandled state: ";


const char
M590_LOG_NO_PIN_REQUIRED[]      PROGMEM = "No PIN was required";

const char
M590_LOG_00[]   PROGMEM = "Shutdown",
                M590_LOG_01[]   PROGMEM = "In Startup",
                                M590_LOG_02[]   PROGMEM = "Module is active.",
                                                M590_LOG_03[]   PROGMEM = "Pin entry is required",
                                                                M590_LOG_04[]   PROGMEM = "Pin entry successful",
                                                                                M590_LOG_05[]   PROGMEM = "Pin is being validated",
                                                                                                M590_LOG_06[]   PROGMEM = "Pin validation successful",
                                                                                                                M590_LOG_07[]   PROGMEM = "Registering on cellular network",
                                                                                                                                M590_LOG_08[]   PROGMEM = "Connected to cellular network",
                                                                                                                                                M590_LOG_09[]   PROGMEM = "Configuring SMS format",
                                                                                                                                                                M590_LOG_10[]   PROGMEM = "Ready for SMS",
                                                                                                                                                                                M590_LOG_11[]   PROGMEM = "A fatal error occured, library can not continue";

//crude method of accessing multiple progmem Strings easily // index corresponds to m590States
const char *M590_LOG[] = {
    M590_LOG_00,
    M590_LOG_01,
    M590_LOG_02,
    M590_LOG_03,
    M590_LOG_04,
    M590_LOG_05,
    M590_LOG_06,
    M590_LOG_07,
    M590_LOG_08,
    M590_LOG_09,
    M590_LOG_10,
    M590_LOG_11,
};


M590::M590(char *text_ptr) {
    _text_ptr = NULL;
    _gsmSerial = NULL;

    String compstr = "";
    char c = EEPROM.read(EEPROM_NUMBER_ADDR);
    int i = 0;
    while (c != '\0' && i < 1024) {
        compstr += c;
        i++;
        c = EEPROM.read(EEPROM_NUMBER_ADDR + i);
    }
    targetNum = compstr;
    
    String compstr = "";
    char c = EEPROM.read(EEPROM_SIMPIN_ADDR);
    int i = 0;
    while (c != '\0' && i < 1024) {
        compstr += c;
        i++;
        c = EEPROM.read(EEPROM_SIMPIN_ADDR + i);
    }
    SIMPIN = compstr;
}

bool M590::begin(unsigned long baudRate = 115200, HardwareSerial *gsmSerial = NULL) {

    _gsmSerial = gsmSerial;
    _gsmSerial->begin(baudRate);
}

void M590::enableDebugSerial(HardwareSerial *debugSerial) {
    if (debugSerial)
        _debugSerial = debugSerial;
}

// Serial passthrough operations
int M590::available() {
    return _gsmSerial->available();
}

char M590::read() {
    return (char) _gsmSerial->read();
}

void M590::write(const char c) {
    _gsmSerial->write(c);
}

void M590::print(const String s) {
    _gsmSerial->print(s);
}

bool M590::initialize(String pin) {
    if (!checkAlive()) {//checkAlive still gets executed
        printDebug(M590_ERROR_NOT_RESPONDING); //TODO: better error handling
        return false;
    }

    checkPinRequired();
    if (_currentState == M590_STATE_PIN_REQUIRED) {
        if (pin && pin != "")
            sendPinEntry(pin); //sets state to pin_entry_done, when successful
        else {
            printDebug(M590_ERROR_NO_PIN);
            return false;
        }
    } else if (_currentState == M590_STATE_FATAL_ERROR)
        return false;

    if (_currentState == M590_STATE_PIN_ENTRY_DONE) {
        _currentState = M590_STATE_PIN_VALIDATION;
        readForAsyncResponse(M590_RESPONSE_PIN_VAL_DONE); //start asnyc reading (execution continued in loop())
    } else if (_currentState == M590_STATE_PIN_VALIDATION_DONE) {
        printDebug(M590_LOG_NO_PIN_REQUIRED);
    } else {
        _currentState = M590_STATE_FATAL_ERROR;
        printDebug(M590_ERROR_WRONG_PIN);
    }
}

//thee loop gets called every arduino code to handle "async" responses
void M590::loop() {
    switch (_currentState) {
        case M590_STATE_STARTUP_DONE:
            break;

        case M590_STATE_PIN_VALIDATION: {
                m590ResponseCode status = readForAsyncResponse(); //call function with last entered parameters
                if (status == M590_SUCCESS)
                    _currentState = M590_STATE_PIN_VALIDATION_DONE;
                else if (status == M590_TIMEOUT) {
                    _currentState = M590_STATE_FATAL_ERROR;
                    printDebug(M590_ERROR_PINVAL_TIMEOUT);
                }
                break;
            }

        case M590_STATE_PIN_VALIDATION_DONE: {
                _currentState = M590_STATE_CELLULAR_CONNECTING;
                break;
            }

        case M590_STATE_CELLULAR_CONNECTING: {
                unsigned long curMillis = millis();
                if (_asyncStartTime == 0) _asyncStartTime = curMillis; //repurpose asyncStartTime variable
                else if (curMillis >= _asyncStartTime + STATUS_POLLING_RATE) {
                    m590NetworkStates netState = checkNetworkState();
                    if (netState == M590_NET_REGISTERED)
                        _currentState = M590_STATE_CELLULAR_CONNECTED;
                    else if (netState == M590_NET_SEARCHING_NOT_REGISTERED) {
                        printDebug("."); //print dots to show wait for registration
                    } else {
                        _currentState = M590_STATE_FATAL_ERROR;
                        printDebug(M590_ERROR_UNHANDLED_NET_STATE);
                        printDebug(String(netState), true);
                    }
                    _asyncStartTime = curMillis;
                }
                break;
            }
        case  M590_STATE_CELLULAR_CONNECTED: {
                _gsmSerial->print((__FlashStringHelper *) M590_COMMAND_PREFIX);
                _gsmSerial->println((__FlashStringHelper *) M590_COMMAND_SET_INPUT_TEXT_MODE);
                bool success = readForResponses(M590_RESPONSE_OK, M590_RESPONSE_FAIL) == M590_SUCCESS;
                if (success) {
                    _currentState = M590_STATE_INPUT_MODE;
                } else {
                    _currentState = M590_STATE_FATAL_ERROR;
                }
                break;
            }
        case M590_STATE_INPUT_MODE: {
                _gsmSerial->print((__FlashStringHelper *) M590_COMMAND_PREFIX);
                _gsmSerial->println((__FlashStringHelper *) M590_COMMAND_SET_INPUT_TEXT_FORMAT);
                bool success = readForResponses(M590_RESPONSE_OK, M590_RESPONSE_FAIL) == M590_SUCCESS;
                if (success) {
                    _currentState = M590_STATE_INPUT_MODE_DONE;
                } else {
                    _currentState = M590_STATE_FATAL_ERROR;
                }

                break;
            }
        case M590_STATE_FATAL_ERROR: {
                //reset the library and try again
                break;
            }
    }
    if (_previousState != _currentState) {
        printDebug(M590_LOG[_currentState]);
    }
    _previousState = _currentState;
}

bool M590::checkAlive(void(*callback)(void)) {
    if (_currentState == M590_STATE_SHUTDOWN) {
        sendCommandWithoutPrefix(M590_AT);
        if (readForResponse(M590_RESPONSE_OK) == M590_SUCCESS) {
            _currentState = M590_STATE_STARTUP_DONE;
            if (callback) callback();
            return true;
        } else
            return false;
    } else return false;
}

bool M590::checkPinRequired() {
    if (_currentState == M590_STATE_STARTUP_DONE) {
        sendCommand(M590_COMMAND_CHECK_PIN);
        memset(_responseBuffer, 0, sizeof(_responseBuffer));
        readForResponse(M590_RESPONSE_OK, _responseBuffer, sizeof(_responseBuffer));
        bool required = bufferStartsWithProgmem(_responseBuffer, M590_RESPONSE_PIN_REQUIRED);
        //check if module does not need pin entry
        bool alreadyReady = bufferStartsWithProgmem(_responseBuffer, M590_RESPONSE_PIN_DONE);
        _currentState = required ? M590_STATE_PIN_REQUIRED : M590_STATE_PIN_VALIDATION_DONE;
        if (!required && !alreadyReady) {
            _currentState = M590_STATE_FATAL_ERROR;
            printDebug(M590_ERROR_OTHER_PIN_ERR);
        }
        return required; //returns true, if pin is required
    } else return false;
}

bool M590::sendPinEntry(String pin, void (*callback)(void)) {
    if (_currentState == M590_STATE_PIN_REQUIRED) {
        _gsmSerial->print((__FlashStringHelper *) M590_COMMAND_PREFIX);
        _gsmSerial->print((__FlashStringHelper *) M590_COMMAND_INPUT_PIN);
        _gsmSerial->print('"');
        _gsmSerial->print(pin);
        _gsmSerial->print('"');
        _gsmSerial->println();
        bool success = readForResponses(M590_RESPONSE_OK, M590_RESPONSE_FAIL) == M590_SUCCESS;
        if (success) _currentState = M590_STATE_PIN_ENTRY_DONE;
        return success;
    }
    return false;
}

m590NetworkStates M590::checkNetworkState() {
    sendCommand(M590_COMMAND_CHECK_NETWORK_STATUS);
    memset(_responseBuffer, 0, sizeof(_responseBuffer));
    m590ResponseCode r = readForResponse(M590_RESPONSE_OK, _responseBuffer, sizeof(_responseBuffer));
    //the fourth char in the response (e.g. " 0,3") will be the registration state (e.g. 3)
    if (r == M590_SUCCESS)
        return (m590NetworkStates) (_responseBuffer[3] - '0'); //convert to integer, maps to m590NetworkStates
    else return M590_NET_PARSE_ERROR;
}


void M590::sendCommand(const char *progmemCommand, const char *params) {
    //need to cast to FlashStringHelper for it to correctly read from progmem
    _gsmSerial->print((__FlashStringHelper *) M590_COMMAND_PREFIX);
    sendCommandWithoutPrefix(progmemCommand, params);
}

void M590::sendCommandWithoutPrefix(const char *progmemCommand, const char *params) {
    _gsmSerial->print((__FlashStringHelper *) progmemCommand);

    if (params && strlen(params))
        _gsmSerial->print(params);

    _gsmSerial->println(); //terminate with CLRF
}

void M590::resetAsyncVariables() {
    _asyncStartTime = 0;
    _asyncBytesMatched = 0;
    _asyncResponseLength = 0;
    _asyncProgmemResponseString = NULL;
}

m590ResponseCode M590::readForAsyncResponse(const char *progmemResponseString, const unsigned int timeout) {
    if (_asyncStartTime == 0)
        _asyncStartTime = millis();
    if (!_asyncProgmemResponseString && progmemResponseString) {
        //save responseString pointer to look for in private variable (so async function can be called without parameters)
        _asyncProgmemResponseString = progmemResponseString;
        _asyncResponseLength = strlen_P(progmemResponseString);
    } else if (!_asyncProgmemResponseString && !progmemResponseString) {
        //return when function is called for the first time without any parameters
        return M590_NO_PARAMETERS;
    }
    if (millis() > _asyncStartTime + timeout) {
        resetAsyncVariables();
        return M590_TIMEOUT;
    }

    while (_gsmSerial->available()) {
        char c = (char) _gsmSerial->read();
        if (c == pgm_read_byte_near(_asyncProgmemResponseString + _asyncBytesMatched)) {
            _asyncBytesMatched++;
            if (_asyncBytesMatched == _asyncResponseLength) {
                resetAsyncVariables();
                return M590_SUCCESS;
            }
        } else
            _asyncBytesMatched = 0;
    }
    return M590_ASYNC_RUNNING;

}

m590ResponseCode M590::readForResponse(const char *progmemResponseString, char *buffer, const unsigned int max_bytes,
                                       const unsigned int timeout) {
    byte dataMatched = 0, dataRead = 0;
    byte readingData = 0; //state
    byte dataLength = strlen_P(M590_RESPONSE_PREFIX);
    byte matched = 0;
    byte responseLength = strlen_P(progmemResponseString);

    unsigned long startTime = millis();

    while (millis() < (startTime + timeout)) {
        if (_gsmSerial->available()) {
            char c = (char) _gsmSerial->read();
            if (c == pgm_read_byte_near(M590_RESPONSE_PREFIX + dataMatched)) { //check if a return data message begins
                dataMatched++;
                if (dataMatched == dataLength) { //when return data begins
                    readingData = 1;
                    dataMatched = 0;
                }
            } else {
                dataMatched = 0;
            }
            if (readingData) { //if in reading return data mode

                if (readingData == 1 && c == ':') //before colon, there is only the command echoed back
                    readingData = 2;
                else if (readingData == 2) { //if at actual data
                    //_debugSerial->print(c);
                    if (c == '\r') { //if reached end of return data
                        readingData = 0;
                    } else {
                        buffer[dataRead] = c;
                        dataRead++;
                        if (dataRead >= (max_bytes - 1)) { //if read more than buffer size
                            buffer[dataRead] = 0;
                            return M590_LENGTH_EXCEEDED;
                        }
                    }
                }
            } else {
                if (c == pgm_read_byte_near(progmemResponseString + matched)) {
                    matched++;
                    if (matched == responseLength) {
                        return M590_SUCCESS;
                    }
                } else
                    matched = 0;

            }
        }
    }
    //timeout reached
    return M590_TIMEOUT;
}

//two counters/indexes
m590ResponseCode M590::readForResponses(const char *progmemResponseString, const char *progmemFailString, const unsigned int timeout) {
    byte passMatched = 0, failMatched = 0;
    byte passResponseLength = strlen_P(progmemResponseString);
    byte failResponseLength = strlen_P(progmemFailString);
    unsigned long startTime = millis();

    while (millis() < (startTime + timeout)) {
        if (_gsmSerial->available()) {
            char c = (char) _gsmSerial->read();

            //check for pass
            if (c == pgm_read_byte_near(progmemResponseString + passMatched)) {
                passMatched++;
                if (passMatched == passResponseLength) {
                    return M590_SUCCESS;
                }
            } else
                passMatched = 0;

            //check for fail
            if (c == pgm_read_byte_near(progmemResponseString + failMatched)) {
                failMatched++;
                if (failMatched == failResponseLength) {
                    return M590_FAILURE;
                }
            } else
                failMatched = 0;
        }
    }
    //timeout reached
    return M590_TIMEOUT;
}

m590ResponseCode M590::serialToBuffer(char *buffer, const char readUntil, const unsigned int maxBytes, const unsigned int timeout) {
    unsigned long startTime = millis();
    unsigned int bytesRead = 0;

    while (millis() < (startTime + timeout)) {
        if (_gsmSerial->available()) {
            buffer[bytesRead] = (char) _gsmSerial->read();

            //check for readUntil character and replace with 0 (null termination)
            if (buffer[bytesRead] == readUntil) {
                buffer[bytesRead] = 0;
                return M590_SUCCESS;
            }

            bytesRead++;

            if (bytesRead >= (maxBytes - 1)) {
                buffer[bytesRead] = 0;
                return M590_LENGTH_EXCEEDED;
            }
        }
    }
    return M590_TIMEOUT;
}

m590ResponseCode M590::readUntil(const char readUntil, const unsigned int timeout) {
    unsigned long startTime = millis();

    while (millis() < (startTime + timeout)) {
        if (_gsmSerial->available()) {
            if (readUntil == _gsmSerial->read()) {
                return M590_SUCCESS;
            }
        }
    }
    return M590_TIMEOUT;
}

bool M590::bufferStartsWithProgmem(char *buffer, const char *progmemString) {
    bool matches = true;
    for (int i = 0; i < strlen_P(progmemString); i++) {
        matches = buffer[i] == pgm_read_byte_near(progmemString + i);
    }
    return matches;
}

void M590::printDebug(const char *progmemString, bool withNewline) {
    if (_debugSerial) {
        _debugSerial->print((__FlashStringHelper *) progmemString);
        if (withNewline) _debugSerial->println();
    }
}

void M590::printDebug(const String s, bool withNewline) {
    if (_debugSerial) {
        _debugSerial->print(s);
        if (withNewline) _debugSerial->println();
    }
}


bool M590::queueSMS() {

    _debugSerial->print(F("SMS: "));
    _debugSerial->println(_text_ptr);

    if (_currentState == M590_STATE_INPUT_MODE_DONE) {

        _gsmSerial->print((__FlashStringHelper *) M590_COMMAND_PREFIX);
        _gsmSerial->print((__FlashStringHelper *) M590_COMMAND_SEND_SMS);
        _gsmSerial->print(targetNum);
        _gsmSerial->println('"');
        if (readUntil('>') == M590_TIMEOUT)return false;
        _gsmSerial->print((char*)_text_ptr);
        _gsmSerial->write(0x1A);
        return readForResponses(M590_RESPONSE_OK, M590_RESPONSE_FAIL, SMS_TIMEOUT) == M590_SUCCESS;
    }
    return false;
}


bool M590::reInit() {
    if (restartRetries >= SW_RETRY_CNT) {
        _debugSerial->println(F("Module SW retries failed, need HW reset!"));
    } else {
        _debugSerial->println(F("Module SW retry"));
        restartRetries++;
        _currentState = M590_STATE_SHUTDOWN;
        resetAsyncVariables();//TODO is this needed?
        initialize("0000");
    }

}

uint8_t M590::newSMSAvailable() {
    if (_currentState != M590_STATE_INPUT_MODE_DONE)return 0;

    _gsmSerial->print((__FlashStringHelper *) M590_COMMAND_PREFIX);
    _gsmSerial->println((__FlashStringHelper *) M590_COMMAND_GET_SMS_CNT);

    memset(_responseBuffer, 0, sizeof(_responseBuffer));

    m590ResponseCode r = readForResponse(M590_RESPONSE_OK, _responseBuffer, sizeof(_responseBuffer));
    //"SM",0,50 or "SM",0,50
    if (r == M590_SUCCESS) {
        _debugSerial->print(F("newSMS sucess : "));
        _debugSerial->println(_responseBuffer);
        return (uint8_t) (_responseBuffer[6] - '0'); //convert to integer, maps to m590NetworkStates
    } else {
        _debugSerial->println(F("newSMS parseError"));
        return M590_NET_PARSE_ERROR;
    }


}


String M590::getSMS() {
    if (_currentState != M590_STATE_INPUT_MODE_DONE)return "";

    _gsmSerial->print((__FlashStringHelper *) M590_COMMAND_PREFIX);
    _gsmSerial->println((__FlashStringHelper *) M590_COMMAND_GET_SMS_ATIDX);
    //TODO get SMS string here
    m590ResponseCode r = readForResponse(M590_RESPONSE_OK, _responseBuffer, sizeof(_responseBuffer));

    _gsmSerial->print((__FlashStringHelper *) M590_COMMAND_PREFIX);
    _gsmSerial->println((__FlashStringHelper *) M590_COMMAND_DEL_SMS_ATIDX);
    if (readForResponses(M590_RESPONSE_OK, M590_RESPONSE_FAIL, COMMAND_TIMEOUT) != M590_SUCCESS)_debugSerial->println(F("getSMS delError"));
}

void M590::setTargetNum(String num) {
    targetNum = num;

    String compstr = "";
    char c = EEPROM.read(EEPROM_NUMBER_ADDR);
    int i = 0;
    while (c != '\0' && i < 1024) {
        compstr += c;
        i++;
        c = EEPROM.read(EEPROM_NUMBER_ADDR + i);
    }

    //Serial1.println("set number "+num);
    if (compstr == num)return;
    //Serial1.println("Update EEPROM with new number");
    for (int i = 0; i < num.length(); i++) {
        EEPROM.write(EEPROM_NUMBER_ADDR + i, num[i]);
    }
    EEPROM.write(EEPROM_NUMBER_ADDR + num.length(), '\0');

}

void M590::setSIMPin(String pin) {
SIMPIN = pin;

    String compstr = "";
    char c = EEPROM.read(EEPROM_SIMPIN_ADDR);
    int i = 0;
    while (c != '\0' && i < 1024) {
        compstr += c;
        i++;
        c = EEPROM.read(EEPROM_SIMPIN_ADDR + i);
    }
    if (compstr == pin)return;
    for (int i = 0; i < pin.length(); i++) {
        EEPROM.write(EEPROM_SIMPIN_ADDR + i, pin[i]);
    }
    EEPROM.write(EEPROM_SIMPIN_ADDR + pin.length(), '\0');
}
