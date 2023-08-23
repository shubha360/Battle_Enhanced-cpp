#ifndef BATTLEGROUND_H
#define BATTLEGROUND_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class BattleGround {
public:
    static const int BATTLEGROUND_WIDTH;
    static const int BATTLEGROUND_HEIGHT;

    BattleGround();
    void printBattleGround();

private:
    vector<string> _battleGrid;

    string _topAndBottomLine;
};

#endif // BATTLEGROUND_H
