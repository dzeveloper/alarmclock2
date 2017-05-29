#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#import <semphr.h>
#include "Beeper.h"

Beeper::Beeper(int pin) {
    this->tonePin = pin;
    pinMode((uint8_t) pin, OUTPUT);
}

void Beeper::beep() {
    beep(800, 300);
}

void Beeper::beep(int freq, int duration) {
    tone((uint8_t) tonePin, (unsigned int) freq, (unsigned long) duration);
    delay((unsigned long) duration);
    noTone((uint8_t) tonePin);
}

void Beeper::noBeep(int duration) {
    noTone((uint8_t) tonePin);
    delay((unsigned long) duration);
}

void Beeper::click() {
    for (int i = 0; i < 8; i++) {
        digitalWrite((uint8_t) tonePin, HIGH);
        digitalWrite((uint8_t) tonePin, LOW);
    }
}