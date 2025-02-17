#include "CMDParser.h"

Parser smsParser;
String input = "";
void setup() {
    Serial1.begin(115200);
    while (!Serial1); // Wait for Serial to initialize
    Serial1.println("Hello there");
}

void loop() {
    while (Serial1.available() > 0) {
        char c = Serial1.read();
        if (c == '\r' || c == '\n') {
            smsParser.parse(input);
            input = "";
        } else {
            input += c;
        }
    }

}
