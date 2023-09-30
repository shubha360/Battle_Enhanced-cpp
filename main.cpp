#include "include/Combat.h"

#include <conio.h>

int main() {
    Combat combat;
    combat.init("files/battle_ground.txt");
    //combat.init("files/test.txt");

    combat.printBattleGround("Press any key to begin war!");

    int input = _getch(); // wait for user input before beginning war

    combat.startBattle(0);
    combat.endBattle();

    return 0;
}