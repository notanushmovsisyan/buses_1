#ifndef BUSES_1_CITY_H
#define BUSES_1_CITY_H

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cstdint>
#include "Street.h"
#include "Crossroad.h"
#include "Bus.h"
#include <stdexcept>

class City {
private:
    int numberOfCrossroads;
    int numberOfStreets;
    std::vector<std::vector<int> > city;
    std::unordered_map<Crossroad*, std::unordered_set<Street*> > crossroadToStreets;
    std::unordered_map<char, Crossroad*> crossroads;
    std::vector<std::vector<int> > shortestPaths;
    std::unordered_set<std::string> busIDs;
    std::vector<Bus*> indexToBus;
    std::vector<Crossroad> crossroadObjects;

    Crossroad* getCrossroad(const char &data) {
        auto crossroadIt = crossroads.find(data);
        if (crossroadIt != crossroads.end()) {
            return crossroadIt->second; //removed &
        }
        return nullptr;
    }

    void floydWarshallAlgo() {
        shortestPaths = city;
        for (int k = 0; k < numberOfCrossroads; k++) {
            for (int i = 0; i < numberOfCrossroads; i++) {
                for (int j = 0; j < numberOfCrossroads; j++) {
                    if (shortestPaths[i][k] != INT_MAX && shortestPaths[k][j] != INT_MAX) {
                        shortestPaths[i][j] = std::min(shortestPaths[i][j], shortestPaths[i][k] + shortestPaths[k][j]);
                    }
                }
            }
        }
    }

public:
    City(int _numberOfCrossroads, int _numberOfStreets, std::vector<Street> _streets)
    : numberOfCrossroads(_numberOfCrossroads), numberOfStreets(_numberOfStreets),
    city(numberOfCrossroads,std::vector<int>(numberOfCrossroads, INT_MAX)),
    shortestPaths(numberOfCrossroads,std::vector<int>(numberOfCrossroads, INT_MAX)) {

        for(int i = 0; i < numberOfCrossroads; ++i) {
            city[i][i] = 0;
            shortestPaths[i][i] = 0;
        }

        for(int k = 0; k < numberOfStreets; ++k) {
            char firstCrossroadValue = _streets[k].getFirst()->getValue();
            char secondCrossroadValue = _streets[k].getSecond()->getValue();

            int i = firstCrossroadValue - 65;
            int j = secondCrossroadValue - 65;

            city[i][j] = _streets[k].getDuration();
            city[j][i] = _streets[k].getDuration();
            shortestPaths[i][j] = _streets[k].getDuration();
            shortestPaths[j][i] = _streets[k].getDuration();
        }

        floydWarshallAlgo();

        for(int i = 0; i < numberOfCrossroads; ++i) {
            char key = (char) (i + 65);
            Crossroad* k = new Crossroad(key); // Create a new Crossroad object
            crossroads[key] = k;
            crossroadObjects.push_back(*k);
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

    void printCrossroads() {
        std::cout << "Crossroads: " << std::endl;
        for (auto it = crossroads.begin(); it != crossroads.end(); ++it) {
            std::cout << it->second->getValue() << " ";
        }
        std::cout << std::endl;
    }

    void printCity() {
        std::cout << "City:" << std::endl;
        for(int i = 0; i < numberOfCrossroads; ++i) {
            for(int j = 0; j < numberOfCrossroads; ++j) {
                std::cout << city[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    void printShortestPaths() {
        std::cout << "Shortest Paths:" << std::endl;
        for(int i = 0; i < numberOfCrossroads; ++i) {
            for(int j = 0; j < numberOfCrossroads; ++j) {
                std::cout << shortestPaths[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    void printBuses() {
        for (const auto& busPtr : indexToBus) {
            const Bus& bus = *busPtr;
            std::cout << "Bus: " << bus.getSource()->getValue() << " to " << bus.getDestination()->getValue() << ", Duration: " << bus.getDuration() << std::endl;
        }
        std::cout << std::endl;
    }


    int add_bus(char A, char B) {
        int i = A - 65;
        int j = B - 65;

        if((i >= numberOfCrossroads || j >= numberOfCrossroads) || shortestPaths[i][j] == INT_MAX ) {
            std::string message = "There is no path between " + std::string(1 ,A) + " and "
                                  + std::string(1,B) + ". A bus can't be added.";
            throw std::invalid_argument(message);
        }

        Crossroad* first = getCrossroad(A);

        if (first == nullptr) {
            throw std::out_of_range("Attempting to access invalid crossroad");
        }

        Crossroad* second = getCrossroad(B);

        if (second == nullptr) {
            throw std::out_of_range("Attempting to access invalid crossroad");
        }

        std::string id = std::to_string(i) + "," + std::to_string(j) + "," + std::to_string(shortestPaths[i][j]);

        if(busIDs.find(id) != busIDs.end()) {
            return shortestPaths[i][j];
        }

        busIDs.insert(id);
        Bus* newBus = new Bus(first, second, shortestPaths[i][j]);
        indexToBus.push_back(newBus);

        return newBus->getDuration();
    }

    std::vector<Bus*> construct_street(char A, char B, int duration) {
        int i = A - 65;
        int j = B - 65;

        if((i >= numberOfCrossroads || j >= numberOfCrossroads) || city[i][j] != INT_MAX) {
            std::string message = "Either there is already a street between " + std::string(1 ,A) + " and "
                                  + std::string(1,B) + " or these crossroads don't exist";
            throw std::invalid_argument(message);
        }

        Crossroad* first = getCrossroad(A);

        if (first == nullptr) {
            throw std::out_of_range("Attempting to access invalid crossroad");
        }

        Crossroad* second = getCrossroad(B);

        if (second == nullptr) {
            throw std::out_of_range("Attempting to access invalid crossroad");
        }

        Street st(*first, *second, duration);

        if (city[i][j] != INT_MAX && city[j][i] != INT_MAX) {
            throw std::invalid_argument("Crossroad already exists");
        }

        city[i][j] = duration;
        city[j][i] = duration;
        crossroadToStreets[first].insert(&st);
        crossroadToStreets[second].insert(&st);

        if(shortestPaths[i][j] > duration) {
            floydWarshallAlgo();

            for (Bus* current : indexToBus) {
                int m = current->getSource()->getValue() - 65;
                int n = current->getDestination()->getValue() - 65;

                if(current->getDuration() > shortestPaths[m][n]) {
                    current->setDuration(shortestPaths[m][n]);
                }
            }
        }
        return indexToBus;
    }
};

#endif //BUSES_1_CITY_H
