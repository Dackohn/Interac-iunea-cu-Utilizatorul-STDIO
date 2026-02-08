#pragma once
#include <Arduino.h>

class SerialStdio {
public:
    static void Begin(unsigned long baudRate);

private:
    static int PutChar(char c, FILE* stream);
    static int GetChar(FILE* stream);
};
