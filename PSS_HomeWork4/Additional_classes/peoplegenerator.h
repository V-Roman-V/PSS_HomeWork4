#ifndef PEOPLEGENERATOR_H
#define PEOPLEGENERATOR_H

#include "People_classes/people.h"
#include <vector>
#include <cstdlib>
#include <ctime>

#include <iostream>

class PeopleGenerator
{
public:
    static People getRandomPeople();

private:
    PeopleGenerator() = delete;

    static unsigned int count;

    struct data{std::string name,surname; Gender gender;};
    static std::vector<data> names;

    static int getDigit(int i);

    struct Initializer{ Initializer() {std::srand(std::time(nullptr));}};
    static Initializer init;
};

#endif // PEOPLEGENERATOR_H
