#pragma once

/*
    This class is the main control point of the battle. 
    The main logic is, every soldier has his own duel where his target is the closest enemy soldier. 
    If he can kill the target, the duel is deleted then he looks for new target and initiates a new duel.
*/

#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

#include "Duel.h"

class Combat {
public:
    Combat();
    ~Combat();

    void init(string combatFile);
    void startBattle(unsigned int attackIntervalInMills); // Makes
    void endBattle();

private:
    vector<string> _battleGround; // main battle ground
    vector<Entity*> _sideOne; // vector of side one
    vector<Entity*> _sideTwo;  // vector of side two
    vector<Duel*> _duels; // vector of duels

    int _sideOneAlive, _sideTwoAlive;
    string _topIndent, _bottomIndent;

    void _printBattleGround();
};
