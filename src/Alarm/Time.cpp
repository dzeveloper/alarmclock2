#include <Time.h>
#include "Time.h"

Time::Time() {
    this->Hour = 0;
    this->Minute = 0;
    this->Second = 0;
}

Time::Time(uint8_t Hour, uint8_t Minute, uint8_t Second) {
    this->Hour = Hour;
    this->Minute = Minute;
    this->Second = Second;
}

bool Time::operator>(Time t) {
    return this->Hour > t.Hour || (this->Hour == t.Hour && this->Minute > t.Minute) ||
           (this->Hour == t.Hour && this->Minute == t.Minute && this->Second > t.Second);
}

bool Time::operator==(Time t) {
    return this->Hour == t.Hour && this->Minute == t.Minute && this->Second == t.Second;
}

bool Time::operator<(Time t) {
    return !(*this > (t)) && !(*this == (t));
}

Time::Time(tmElements_t t) {
    this->Hour = t.Hour;
    this->Minute = t.Minute;
    this->Second = t.Second;
}
