#include <iostream>
#include "../include/City.h"
#include <vector>

void test1() {
    City c(6);
    std::vector<std::pair<char, char> > streets;
    std::vector<int> durations;

    std::pair<char, char> p1 = std::make_pair('A', 'B');
    std::pair<char, char> p2 = std::make_pair('B', 'C');
    std::pair<char, char> p3 = std::make_pair('D', 'E');
    std::pair<char, char> p4 = std::make_pair('E', 'F');

    streets.push_back(p1);
    streets.push_back(p2);
    streets.push_back(p3);
    streets.push_back(p4);

    for (int i = 0; i < streets.size(); ++i) {
        std::cout << streets[i].first << " " << streets[i].second << std::endl;
    }

    durations = {1, 2, 3, 5};

    for (int i = 0; i < durations.size(); ++i) {
        std::cout << durations[i] << std::endl;
    }
}

int main() {
    test1();

    return 0;
}
