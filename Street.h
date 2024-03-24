//
// Created by Nare on 3/23/2024.
//

#ifndef BUSES_1_STREET_H
#define BUSES_1_STREET_H

class Street {
private:
    const Crossroad A;
    const Crossroad B;
    int duration;

public:
    Street(const Crossroad &_A, const Crossroad &_B, int &_duration) : A(_A), B(_B), duration(_duration) {}

    Crossroad getFirst() const {
        return A;
    }

    Crossroad getSecond() const {
        return B;
    }

    int getDuration() {
        return duration;
    }

    void setFirst(Crossroad new_A) {
        A = new_A;
    }

    void setSecond(Crossroad new_B) {
        B = new_B;
    }

    void setDuration(int newDuration) {
        duration = newDuration;
    }

    ~Street() {}
};
#endif //BUSES_1_STREET_H
