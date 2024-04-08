//
// Created by Anoush Movsisian on 26.03.24.
//

#ifndef BUSES_1_BUS_H
#define BUSES_1_BUS_H

#include "Crossroad.h"
#include <functional>

class Bus {
private:
    Crossroad* source;
    Crossroad* dest;
    int duration;

public:
    Bus() = default;
    Bus(Crossroad* _s, Crossroad* _d) : source(_s), dest(_d), duration(0) {}
    Bus(Crossroad* _s, Crossroad* _d, int _dur) : source(_s), dest(_d), duration(_dur) {}

    Crossroad* getSource() const {
        return source;
    }

    Crossroad* getDestination() const {
        return dest;
    }

    int getDuration() const {
        return duration;
    }

    void setDuration(int dur) {
        duration = dur;
    }
};

#endif //BUSES_1_BUS_H
