#include <Arduino.h>

class Button {
    uint8_t pin;
    int min, max;
    unsigned long delayMs, lastPressMs = 0;
    void construct(uint8_t pin, int min, int max, unsigned long delayMs);


public:
    Button(uint8_t pin, int min, int max);

    Button(uint8_t pin, int min, int max, long delayMs);

    bool check();
};