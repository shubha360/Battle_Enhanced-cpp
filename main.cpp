#include "include/Combat.h"

int main() {
    Combat combat;
    combat.init("files/battle_ground.txt");
    //combat.init("files/test.txt");
    combat.startBattle(10);
    combat.endBattle();

    return 0;
}
