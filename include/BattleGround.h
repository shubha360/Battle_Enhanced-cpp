#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "Entity.h"

using namespace std;

class BattleGround {
public:
    static const int BATTLEGROUND_WIDTH;
    static const int BATTLEGROUND_HEIGHT;

    BattleGround();
    void printBattleGround();

    void setEntity(Entity* entity);

private:
    vector<string> _battleGrid;

    string _topAndBottomLine;
};
