#pragma once

#include <iostream>
#include <string>
#include <fstream>

#include "Duel.h"

class Combat {
public:
    Combat();
    ~Combat();

    void init();
    void startBattle();
    void endBattle();

    void printBattleGround();

private:
    vector<string> _battleGround;
    vector<Entity*> _sideOne;
    vector<Entity*> _sideTwo;
    vector<Duel*> _duels;

    int _sideOneAlive, _sideTwoAlive;
    string _topIndent;
};
