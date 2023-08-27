#include "include/Combat.h"

int main() {
    Combat combat;
    combat.init("files/battle_ground.txt");
    combat.startBattle();
    combat.endBattle();

    return 0;
}
