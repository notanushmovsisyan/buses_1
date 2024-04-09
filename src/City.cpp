#include "../include/City.h"

Crossroad* City::getCrossroad(const char &data) {
    auto crossroadIt = crossroads.find(data);
    if (crossroadIt != crossroads.end()) {
        return crossroadIt->second;
    }
    return nullptr;
}

void City::floydWarshall() {
    shortestPaths = city;
    for (int k = 0; k < numberOfCrossroads; k++) {
        for (int i = 0; i < numberOfCrossroads; i++) {
            if (shortestPaths[i][k] != INT_MAX) {
                for (int j = 0; j < numberOfCrossroads; j++) {
                    if (shortestPaths[k][j] != INT_MAX) {
                        shortestPaths[i][j] = std::min(shortestPaths[i][j], shortestPaths[i][k] + shortestPaths[k][j]);
                    }
                }
            }
        }
    }
}

City::City(int numOfCrossroads)
        : numberOfCrossroads(numOfCrossroads),
          city(numberOfCrossroads,std::vector<int>(numberOfCrossroads, INT_MAX)) {
    for (int i = 0; i < numberOfCrossroads; ++i) {
        city[i][i] = 0;
        char value = (char)(i + 65);
        Crossroad* newCrossroad = new Crossroad(value);
        crossroads[value] = newCrossroad;
        crossroadToStreets[newCrossroad] = std::unordered_set<Street *>();
    }
}

bool City::addStreets(std::vector<std::pair<char, char> > crossroadValues, std::vector<int> durations) {
    if (crossroadValues.size() != durations.size()) {
        return false;
    }

    for(int i = 0; i < crossroadValues.size(); ++i) {
        Crossroad *source = getCrossroad(crossroadValues[i].first);

        if (source == nullptr) {
            return false;
        }

        Crossroad *destination = getCrossroad(crossroadValues[i].second);

        if (destination == nullptr) {
            return false;
        }

        Street *newStreet = new Street(source, destination, durations[i]);

        if (crossroadToStreets.find(source) == crossroadToStreets.end()
            || crossroadToStreets.find(destination) == crossroadToStreets.end()) {
            return false;
        }

        crossroadToStreets[source].insert(newStreet);
        crossroadToStreets[destination].insert(newStreet);
    }

    for (auto it : crossroadToStreets) {
        for (auto itStreet : it.second) {
            std::cout << itStreet->getSource()->getValue() << " " << itStreet->getDestination()->getValue() << " "
                      << itStreet->getDuration() << std::endl;
        }
    }

    return true;
}

int City::addBus(const char &source, const char &destination) {
    int i = source - 65;
    int j = destination - 65;

    if((i >= numberOfCrossroads || j >= numberOfCrossroads) || shortestPaths[i][j] == INT_MAX ) {
        std::string message = "There is no path between " + std::string(1 ,source) + " and "
                              + std::string(1,destination) + ". A bus can't be added.";
        throw std::invalid_argument(message);
    }

    Crossroad *first = getCrossroad(source);

    //probably not out_of_range
    if (first == nullptr) {
        throw std::out_of_range("Attempting to access invalid crossroad");
    }

    Crossroad *second = getCrossroad(destination);

    if (second == nullptr) {
        throw std::out_of_range("Attempting to access invalid crossroad");
    }

    std::string id = std::to_string(source) + std::to_string(destination);

    if(busIDs.find(id) != busIDs.end()) {
        return shortestPaths[i][j];
    }

    busIDs.insert(id);
    Bus *newBus = new Bus(first, second);
    newBus->setDuration(shortestPaths[i][j]);

    return newBus->getDuration();
}

std::vector<Bus *> City::constructStreet(const char &source, const char &destination, int duration) {}

std::vector<std::vector<char> > City::details(int busIndex) {}
