#ifndef BUSES_1_BUS_H
#define BUSES_1_BUS_H

#include "Crossroad.h"
#include <functional>

#include "Crossroad.h"

class Bus {
private:
    Crossroad *source;
    Crossroad *destination;
    int duration;

public:
    Bus(Crossroad *src, Crossroad *dest);
    Crossroad *getSource();
    Crossroad *getDestination();
    int getDuration();
    void setDuration(int newDuration);
};

#endif //BUSES_1_BUS_H
