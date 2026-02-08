#pragma once
#include <Arduino.h>

class LedController {
public:
    explicit LedController(uint8_t pin);

    void Begin();
    void Set(bool on);
    bool IsOn() const;

private:
    uint8_t Pin;
    bool State;
};
