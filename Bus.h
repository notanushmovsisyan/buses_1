//
// Created by Anoush Movsisian on 26.03.24.
//

#ifndef BUSES_1_BUS_H
#define BUSES_1_BUS_H

#include "Crossroad.h"

class Bus {
private:
    Crossroad* source;
    Crossroad* dest;
    int duration;

public:
    Bus() = default;
    Bus(Crossroad* _s, Crossroad* _d) : source(source), dest(_d), duration(0) {}
    Bus(Crossroad* _s, Crossroad* _d, int _dur) : source(source), dest(_d), duration(_dur) {}

    Crossroad* getSource() {
        return source;
    }

    Crossroad* getDestination() {
        return dest;
    }

    int getDuration() {
        return duration;
    }

    void setDuration(int dur) {
        duration = dur;
    }
};

#endif //BUSES_1_BUS_H
