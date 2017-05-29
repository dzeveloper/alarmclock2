#ifndef ALARMCLOCK_TIME_H
#define ALARMCLOCK_TIME_H

#include <TimeLib.h>

class Time : public tmElements_t {
public:
    Time();

    Time(uint8_t Year, uint8_t Month, uint8_t Day, uint8_t Hour, uint8_t Minute, uint8_t Second);

    inline bool operator>(Time t);
    inline bool operator==(Time t);
    inline bool operator<(Time t);
};

#endif //ALARMCLOCK_TIME_H
