#ifndef COMBAT_H
#define COMBAT_H

#include <iostream>
#include <string>
#include <conio.h>

using namespace std;

class Combat {
public:
    Combat();
    void init();

private:
    string _firstSideName, _secondSideName;
    int _firstSideEntities, _secondSideEntities;
    char _firstSideSign, _secondSideSign;

    string _takeStringInput(string prompt);
    char _takeCharInput(string prompt);
    int _takeIntInput(string prompt);
};

#endif // COMBAT_H
