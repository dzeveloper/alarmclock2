#ifndef ALARMCLOCK_BEEPER_H
#define ALARMCLOCK_BEEPER_H

class Beeper {
    int tonePin;
public:
    Beeper(int pin);

    void beep();

    void beep(int freq, int duration);

    void noBeep(int duration);

    void click();
};

#endif //ALARMCLOCK_BEEPER_H