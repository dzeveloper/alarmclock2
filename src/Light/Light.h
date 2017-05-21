#ifndef ALARMCLOCK_LIGHT_H
#define ALARMCLOCK_LIGHT_H

#include <Arduino.h>

class Light {
    bool condition;
    uint8_t pin, led_pin;
public:
    Light(uint8_t pin, uint8_t led_pin);

    bool getCondition();

    void turnOn();

    void turnOff();
};

#endif //ALARMCLOCK_LIGHT_H