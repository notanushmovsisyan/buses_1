#ifndef BUSES_1_CROSSROAD_H
#define BUSES_1_CROSSROAD_H

#include <iostream>

class Crossroad {
private:
    char value;

public:
    Crossroad() = default;

    Crossroad(const char &_value) : value(_value) {}

    char getValue() const {
        return value;
    }

    ~Crossroad() = default;
};

#endif //BUSES_1_CROSSROAD_H
