#include "Time.h"

Time::Time() {
    this->Year = 0;
    this->Month = 0;
    this->Day = 0;
    this->Hour = 0;
    this->Minute = 0;
    this->Second = 0;
}

Time::Time(uint8_t Year, uint8_t Month, uint8_t Day, uint8_t Hour, uint8_t Minute, uint8_t Second) {
    this->Year = Year;
    this->Month = Month;
    this->Day = Day;
    this->Hour = Hour;
    this->Minute = Minute;
    this->Second = Second;
}

bool Time::operator>(Time t) {
    return this->Year > t.Year || this->Month > t.Month || this->Day > t.Day ||
           this->Hour > t.Hour || this->Minute > t.Minute || this->Second > t.Second;
}

bool Time::operator==(Time t) {
    return this->Year == t.Year || this->Month == t.Month || this->Day == t.Day ||
           this->Hour == t.Hour || this->Minute == t.Minute || this->Second == t.Second;
}

bool Time::operator<(Time t) {
    return !(*this > (t) && *this == (t));
}