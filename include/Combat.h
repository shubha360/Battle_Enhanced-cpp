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

    void init(std::string combatFile);
    void startBattle(unsigned int attackIntervalInMills);
    void endBattle();

    void printBattleGround(std::string promptText);

private:
    std::vector<std::string> _battleGround; // main battle ground
    std::vector<Entity*> _armyOne; // vector of side one
    std::vector<Entity*> _armyTwo;  // vector of side two
    std::vector<Duel*> _duels; // vector of duels

    int _armyOneAlive, _armyTwoAlive;
};
