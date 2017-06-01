#include "Light.h"

Light::Light(uint8_t pin, uint8_t led_pin) {
    this->pin = pin;
    this->led_pin = led_pin;
    condition = false;
    pinMode(pin, OUTPUT);
}

bool Light::getCondition() {
    return condition;
}

void Light::turnOn() {
    if (condition)
        return;
    digitalWrite(pin, HIGH);
    digitalWrite(led_pin, HIGH);
    Serial.println("LIGHT IS ON");
    condition = 1;
}

void Light::turnOff() {
    if (!condition)
        return;
    digitalWrite(pin, LOW);
    digitalWrite(led_pin, LOW);
    Serial.println("LIGHT IS OFF");
    condition = false;
}
