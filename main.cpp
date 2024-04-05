#include <iostream>
#include "City.h"

void test1() {
    int numberOfCrossroads = 6;
    int numberOfStreets = 6;
    std::vector<Street> streets;

    Street s1('A', 'B', 2);
    Street s2('C', 'B', 4);
    Street s3('D', 'A', 6);
    Street s4('B', 'E', 3);
    Street s5('D', 'E', 5);
    Street s6('E', 'F', 1);

    streets.push_back(s1);
    streets.push_back(s2);
    streets.push_back(s3);
    streets.push_back(s4);
    streets.push_back(s5);
    streets.push_back(s6);

    City c(numberOfCrossroads, numberOfStreets, streets);


    c.printCity();
    c.printShortestPaths();
    std::cout << "Bus from A to B " << c.add_bus('A', 'B') << std::endl;
    std::cout << "Bus from A to F " << c.add_bus('A', 'F') << std::endl;
}

int main() {

    test1();

    return 0;
}
