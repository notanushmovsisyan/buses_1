#include "../include/Bus.h"

Bus::Bus(Crossroad *src, Crossroad *dest) : source(src), destination(dest), duration(0) {}

Crossroad *Bus::getSource() {
    return source;
}

Crossroad *Bus::getDestination() {
    return destination;
}

int Bus::getDuration() {
    return duration;
}

void Bus::setDuration(int newDuration) {
    duration = newDuration;
}
