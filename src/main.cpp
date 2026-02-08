#include <Arduino.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "SerialStdio.h"
#include "LedController.h"

/*
  Main Application
  ----------------
  Purpose:
    - Initialize STDIO-over-Serial
    - Read commands using scanf()
    - Interpret: "led on" / "led off"
    - Control LED and print confirmation messages

  Input format:
    Two tokens (words) separated by spaces:
      token1 token2
    Example:
      led on
      led off
*/

static const uint8_t LedPin = 7;
static LedController Led(LedPin);

static void PrintHelp() {
    printf("Ready (STDIO over UART).\n");
    printf("Commands:\n");
    printf("  led on   - turn LED ON\n");
    printf("  led off  - turn LED OFF\n");
    printf("Type a command and press Enter.\n\n");
}

static void ToLowerInPlace(char* s) {
    for (; *s; ++s) {
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

    // Prompt is printed using STDIO (printf). fflush ensures it appears immediately.
    printf("> ");
    fflush(stdout);

    /*
      scanf() reads formatted input from stdin (which we mapped to Serial).
      "%15s %15s" reads two whitespace-separated tokens (max 15 chars + '\0').
      It returns the number of successfully read items:
        - 2 means cmd and arg read correctly
        - otherwise, input was invalid or incomplete
    */
    int readCount = scanf("%15s %15s", cmd, arg);

    if (readCount != 2) {
        // If the user types something not matching two tokens, notify and continue.
        printf("ERR: invalid input. Use: led on | led off\n");

        // Without a line-flush helper, we still proceed; next input may finish parsing.
        // Users should enter complete commands with two words.
        return;
    }

    // Normalize case so commands work regardless of user capitalization
    ToLowerInPlace(cmd);
    ToLowerInPlace(arg);

    // Interpret commands
    if (strcmp(cmd, "led") == 0 && strcmp(arg, "on") == 0) {
        Led.Set(true);
        printf("OK: LED ON (pin %d)\n", LedPin);
    } else if (strcmp(cmd, "led") == 0 && strcmp(arg, "off") == 0) {
        Led.Set(false);
        printf("OK: LED OFF (pin %d)\n", LedPin);
    } else {
        // Unknown command pattern
        printf("ERR: unknown command: %s %s\n", cmd, arg);
        printf("Hint: led on | led off\n");
    }
}