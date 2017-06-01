#ifndef ALARMCLOCK_TIME_H
#define ALARMCLOCK_TIME_H

#include <TimeLib.h>

class Time {
public:
    uint8_t Hour, Minute, Second;

    Time();

    Time(uint8_t Hour, uint8_t Minute, uint8_t Second);

    Time(tmElements_t t);

    bool operator>(Time t);

    bool operator==(Time t);

    bool operator<(Time t);
};

#endif //ALARMCLOCK_TIME_H