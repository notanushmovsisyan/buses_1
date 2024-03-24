//
// Created by Nare on 3/23/2024.
//

#ifndef BUSES_1_CROSSROAD_H
#define BUSES_1_CROSSROAD_H

//#include <functional>

class Crossroad {
private:
    const char value;

public:
    Crossroad(const char &_value) : value(_value) {}

    char getValue() const {
        return value;
    }

    ~Crossroad() {}
};

#endif //BUSES_1_CROSSROAD_H
