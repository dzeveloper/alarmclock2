#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#import <semphr.h>
#include "Beeper.h"

SemaphoreHandle_t beeperMutex;

Beeper::Beeper(int pin) {
    if (beeperMutex == NULL) {
        beeperMutex = xSemaphoreCreateMutex();
        if ((beeperMutex) != NULL)
            xSemaphoreGive((beeperMutex));
    }

    this->tonePin = pin;
    pinMode(pin, OUTPUT);
}

void Beeper::beep() {
    beep(800, 300);
}

void Beeper::beep(int freq, int duration) {
    if (xSemaphoreTake(beeperMutex, 0) == pdTRUE) {
        tone((uint8_t) tonePin, (unsigned int) freq, (unsigned long) duration);
//        vTaskDelay(duration/portTICK_PERIOD_MS);
        delay((unsigned long) duration);
        noTone((uint8_t) tonePin);
        xSemaphoreGive(beeperMutex);
    }
}

void Beeper::noBeep(int duration) {
    if (xSemaphoreTake(beeperMutex, 0) == pdTRUE) {
        noTone((uint8_t) tonePin);
//        vTaskDelay(duration/portTICK_PERIOD_MS);
        delay((unsigned long) duration);
        xSemaphoreGive(beeperMutex);
    }
}

void Beeper::click() {
    for (int i = 0; i < 8; i++) {
        digitalWrite((uint8_t) tonePin, HIGH);
        digitalWrite((uint8_t) tonePin, LOW);
    }
}