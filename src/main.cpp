#include <Arduino.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "SerialStdio/SerialStdio.h"
#include "LedController/LedController.h"

static LedController Led(7);

static void PrintHelp() {
    printf("Ready (STDIO mode).\r\n");
    printf("Commands:\r\n");
    printf("  led on\r\n");
    printf("  led off\r\n");
    printf("Example: type: led on <Enter>\r\n\n");
}

static void ToLowerInPlace(char* s) {
    for (; *s; s++) {
        *s = static_cast<char>(tolower(static_cast<unsigned char>(*s)));
    }
}

void setup() {
    SerialStdio::Begin(9600);
    Led.Begin();
    PrintHelp();
}

void loop() {
    char cmd[16];
    char arg[16];

    printf("> ");
    fflush(stdout);

    int readCount = scanf("%15s %15s", cmd, arg);

    if (readCount != 2) {
        printf("ERR: invalid input. Use: led on | led off\r\n");
        return;
    }

    ToLowerInPlace(cmd);
    ToLowerInPlace(arg);


    if (strcmp(cmd, "led") == 0 && strcmp(arg, "on") == 0) {
        Led.Set(true);
        printf("OK: LED ON (pin %d)\r\n", 7);
    } else if (strcmp(cmd, "led") == 0 && strcmp(arg, "off") == 0) {
        Led.Set(false);
        printf("OK: LED OFF (pin %d)\r\n", 7);
    } else {
        printf("ERR: unknown command: %s %s\r\n", cmd, arg);
        printf("Hint: led on | led off\r\n");
    }
}
