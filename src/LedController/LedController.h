#pragma once
#include <Arduino.h>

/*
  LedController
  -------------
  Purpose:
    Encapsulate all LED GPIO operations in one reusable module.

  Why:
    - main.cpp should not directly manipulate pins (better separation of concerns)
    - easier reuse in future labs (e.g., multiple LEDs, other outputs)
*/
class LedController {
public:
    explicit LedController(uint8_t pin);

    // Configures the pin as output and sets a known initial state (OFF)
    void Begin();

    // Sets LED state: true -> ON, false -> OFF
    void Set(bool on);

    // Returns the last state written to the pin
    bool IsOn() const;

private:
    uint8_t Pin;
    bool State;
};