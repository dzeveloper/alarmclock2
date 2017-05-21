#include "Button.h"

void Button::construct(uint8_t pin, int min, int max, unsigned long delayMs) {
    this->pin = pin;
    this->min = min;
    this->max = max;
    this->delayMs = delayMs;
    pinMode(pin, INPUT_PULLUP);
}

Button::Button(uint8_t pin, int min, int max) {
    construct(pin, min, max, 500);
}

Button::Button(uint8_t pin, int min, int max, long delayMs) {
    construct(pin, min, max, delayMs);
}

bool Button::check() {
    unsigned long ts = millis();
    int val = analogRead(pin);
    if (val > min && val < max && ts > lastPressMs + delayMs) {
        lastPressMs = ts;
        return true;
    }
    return false;
}