#ifndef BUSES_1_CITY_H
#define BUSES_1_CITY_H

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cstdint>
#include "Street.h"
#include "Crossroad.h"


class City {
private:
    int numberOfCrossroads;
    int numberOfStreets;
    std::vector<std::vector<int>> city;
    std::unordered_map<Crossroad*, std::unordered_set<Street*>> crossroadToStreets;
    std::vector<int> buses;
    std::unordered_map<char, Crossroad> crossroads;

    Crossroad* getCrossroad(const char &data) {
        auto crossroadIt = crossroads.find(data);
        if(crossroadIt != crossroads.end()) {
            return &(crossroadIt->second);
        }
        return nullptr;
    }

public:
    City(int _numberOfCrossroads, int _numberOfStreets, std::vector<Street> _streets) : numberOfCrossroads(_numberOfCrossroads), numberOfStreets(_numberOfStreets), city(numberOfCrossroads,std::vector<int>(numberOfCrossroads, INT8_MAX)) {
        for(int i = 0; i < numberOfCrossroads; ++i) {
            for(int j = 0; j < numberOfCrossroads; ++j) {
                if(i == j) {
                    city[i][j] = 0;
                }
            }
        }

        for(int k = 0; k < numberOfStreets; ++k) {
                char firstCrossroadValue = _streets[k].getFirst()->getValue();
                char secondCrossroadValue = _streets[k].getSecond()->getValue();

                int i = firstCrossroadValue - 65;
                int j = secondCrossroadValue - 65;

                city[i][j] = _streets[k].getDuration();
        }

        for(int i = 0; i < numberOfCrossroads; ++i) {
            char k = (char) (i + 65);
            Crossroad* key = getCrossroad(k);

            for(int j = 0; j < numberOfStreets; ++j) {
                if(_streets[j].getFirst() == key || _streets[j].getSecond() == key) {
                    crossroadToStreets[key].insert(&_streets[j]);
                }
            }
        }
    }

    ~City() = default;

    void print() {
        for(int i = 0; i < numberOfCrossroads; ++i) {
            for(int j = 0; j < numberOfCrossroads; ++j) {
                std::cout << city[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
};
#endif //BUSES_1_CITY_H
