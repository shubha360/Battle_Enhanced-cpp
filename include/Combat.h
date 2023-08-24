#pragma once

#include <iostream>
#include <string>
#include <conio.h>

#include "Entity.h"
#include "BattleGround.h"

using namespace std;

class Combat {
public:
    Combat();
    void init();
    void startBattle();

private:
    string _firstSideName, _secondSideName;
    int _firstSideEntities, _secondSideEntities;
    char _firstSideSign, _secondSideSign;

    BattleGround _battleGround;
    Entity _entity1, _entity2;

    string _takeStringInput(string prompt);
    char _takeCharInput(string prompt);
    int _takeIntInput(string prompt);
};
