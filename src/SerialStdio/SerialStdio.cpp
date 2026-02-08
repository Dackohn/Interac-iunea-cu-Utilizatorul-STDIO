#include "SerialStdio.h"

/*
  NOTE about newline behavior:
  Many serial terminals send Enter as '\r' (CR) or "\r\n".
  STDIO parsing usually expects '\n'. To make input consistent, we convert '\r' -> '\n'.
*/

static FILE SerialStream;

void SerialStdio::Begin(unsigned long baudRate) {
    Serial.begin(baudRate);

    // Some boards require waiting for Serial to become ready.
    // On Arduino Uno it returns quickly, but leaving it here keeps code portable.
    while (!Serial) { }

    // Create a FILE stream using our PutChar/GetChar callbacks and bind it to STDIO.
    fdev_setup_stream(&SerialStream, SerialStdio::PutChar, SerialStdio::GetChar, _FDEV_SETUP_RW);
    stdout = &SerialStream;
    stdin  = &SerialStream;
}

int SerialStdio::PutChar(char c, FILE* /*stream*/) {
    // Send one character to the UART
    Serial.write(static_cast<uint8_t>(c));
    return 0;
}

int SerialStdio::GetChar(FILE* /*stream*/) {
    // Block until at least one byte is available from UART
    while (Serial.available() == 0) { }

    int c = Serial.read();

    // Normalize CR to LF to ensure scanf() works consistently across terminals
    if (c == '\r') return '\n';

    return c;
}