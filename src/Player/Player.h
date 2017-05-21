#ifndef ALARMCLOCK_Player_H
#define ALARMCLOCK_Player_H

#include <Beeper/Beeper.h>
#include <Arduino.h>

class Player {
    Beeper *beeper;
public:
    constexpr static char *song = (char *const) "Flinstones:d=4,o=5,b=40:32p,16f6,16a#,16a#6,32g6,16f6,16a#.,16f6,32d#6,32d6,32d6,32d#6,32f6,16a#,16c6,d6,16f6,16a#.";

//    constexpr static char *song = (char *const) "sonic:d=4,o=5,b=125:16c7,32p,8a6,32p,16c7,32p,8b6,32p,16c7,32p,8b6,32p,g6,p,16a6,32p,16e7,32p,8d7,32p,16c7,32p,8b6,32p,16c7,32p,8b6,32p,g6,p,16c7,32p,8a6,32p,16c7,32p,8b6,32p,16c7,32p,8b6,32p,g6,p,16a6,32p,8f6,32p,16a6,32p,8g6,32p,16a6,32p,8g6,32p,c6";
//    constexpr static char *song = (char *) "mario:d=4,o=5,b=100:16e6,16e6,32p,8e6,16c6,8e6,8g6,8p,8g,8p,8c6,16p,8g,16p,8e,16p,8a,8b,16a#,8a,16g.,16e6,16g6,8a6,16f6,8g6,8e6,16c6,16d6,8b,16p,8c6,16p,8g,16p,8e,16p,8a,8b,16a#,8a,16g.,16e6,16g6,8a6,16f6,8g6,8e6,16c6,16d6,8b,8p,16g6,16f#6,16f6,16d#6,16p,16e6,16p,16g#,16a,16c6,16p,16a,16c6,16d6,8p,16g6,16f#6,16f6,16d#6,16p,16e6,16p,16c7,16p,16c7,16c7,p,16g6,16f#6,16f6,16d#6,16p,16e6,16p,16g#,16a,16c6,16p,16a,16c6,16d6,8p,16d#6,8p,16d6,8p,16c6";
//    constexpr static char *song = (char *) "mario:d=4,o=5,b=100:16e6,16e6,32p,8e6,16c6,8e6,8g6,8p,8g,8p,8c6,16p,8g,16p,8e,16p,8a,8b,16a#,8a,16g.,16e6";

    Player(Beeper *beeper);

    void play_rtttl(char *p);
};

#endif //ALARMCLOCK_Player_H
