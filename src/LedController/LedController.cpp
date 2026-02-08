#include "LedController.h"

LedController::LedController(uint8_t pin)
    : Pin(pin), State(false) {}

void LedController::Begin() {
    pinMode(Pin, OUTPUT);
    Set(false);
}

void LedController::Set(bool on) {
    State = on;
    digitalWrite(Pin, on ? HIGH : LOW);
}

bool LedController::IsOn() const {
    return State;
}
