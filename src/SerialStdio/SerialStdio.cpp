#include "SerialStdio.h"
#include <stdio.h>

static FILE SerialStream;

void SerialStdio::Begin(unsigned long baudRate) {
    Serial.begin(baudRate);
    while (!Serial) { }

    fdev_setup_stream(&SerialStream, SerialStdio::PutChar, SerialStdio::GetChar, _FDEV_SETUP_RW);
    stdout = &SerialStream;
    stdin  = &SerialStream;
}

int SerialStdio::PutChar(char c, FILE* ) {
    Serial.write(static_cast<uint8_t>(c));
    return 0;
}

int SerialStdio::GetChar(FILE* ) {
    while (Serial.available() == 0) { }
    return Serial.read();
}
