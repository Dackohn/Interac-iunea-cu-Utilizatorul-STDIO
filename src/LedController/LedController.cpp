#include "LedController.h"

LedController::LedController(uint8_t pin)
    : Pin(pin), State(false) {}

void LedController::Begin() {
    pinMode(Pin, OUTPUT);
    Set(false); // Start with LED OFF
}

void LedController::Set(bool on) {
    State = on;

    // Digital output controls the LED:
    // HIGH means 5V on the pin (LED on in our wiring), LOW means 0V (LED off).
    digitalWrite(Pin, on ? HIGH : LOW);
}

bool LedController::IsOn() const {
    return State;
}