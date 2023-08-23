#include "BattleGround.h"

const int BattleGround::BATTLEGROUND_WIDTH = 70;
const int BattleGround::BATTLEGROUND_HEIGHT = 20;

BattleGround::BattleGround() {
    for (int i = 0; i < BATTLEGROUND_HEIGHT; i++) {
        _battleGrid.push_back(string(BATTLEGROUND_WIDTH, ' '));
    }
    _topAndBottomLine = string(BATTLEGROUND_WIDTH, '=');
}

void BattleGround::printBattleGround() {
    string ground = "";

    for (int row = -1; row <= BATTLEGROUND_HEIGHT; row++) {
        if (row == -1 || row == BATTLEGROUND_HEIGHT) {
            ground += "  " + _topAndBottomLine;
        }
        else {
            ground += " |" + _battleGrid[row] + "|";
        }
        ground += "\n";
    }
    ground += "\n";

    cout << ground;
}
