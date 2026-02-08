#pragma once
#include <Arduino.h>
#include <stdio.h>

/*
  SerialStdio
  ----------
  Purpose:
    Provide a bridge between Arduino Serial (UART) and the C STDIO interface.
    After initialization, functions like printf(), scanf(), getchar() work over UART.

  Idea:
    - stdout/stderr -> Serial.write()
    - stdin         -> Serial.read()
*/
class SerialStdio {
public:
    // Initializes Serial UART and binds STDIO streams to it
    static void Begin(unsigned long baudRate);

private:
    // Called by printf()/puts()/putchar() to output one character
    static int PutChar(char c, FILE* stream);

    // Called by scanf()/getchar()/fgets() to read one character
    static int GetChar(FILE* stream);
};