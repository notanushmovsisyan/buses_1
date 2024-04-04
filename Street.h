#ifndef BUSES_1_STREET_H
#define BUSES_1_STREET_H

#include "Crossroad.h"

class Street {
private:
    Crossroad A;
    Crossroad B;
    int duration;

public:
    Street() = default;

    Street(const Crossroad &A, const Crossroad &B, int _duration) : A(A), B(B), duration(_duration) {}

    Street(char aValue, char bValue, int _duration) : A(aValue), B(bValue), duration(_duration) {}

    const Crossroad* getFirst() const {
        return &A;
    }

    const Crossroad* getSecond() const {
        return &B;
    }

    int getDuration() const {
        return duration;
    }

    void setFirst(Crossroad &new_A) {
        A = new_A;
    }

    void setSecond(Crossroad &new_B) {
        B = new_B;
    }

    void setDuration(int newDuration) {
        duration = newDuration;
    }

    ~Street() = default;
};
#endif //BUSES_1_STREET_H
