#include "../include/Combat.h"

Combat::Combat() {
    _armyOneAlive = 0;
    _armyTwoAlive = 0;
}

Combat::~Combat() {
    endBattle();
}

/*
    Mainly reads the battle ground and soldiers from file and initializes the starting duels
*/
void Combat::init(std::string combatFile) {
    static std::ifstream inputFile;

    inputFile.open(combatFile);
    if (inputFile.fail()) {
        perror(combatFile.c_str());
        return;
    }

    std::string line;

    while (getline(inputFile, line)) {
        _battleGround.push_back(line);

        if (line[0] == '|') {
            for (int i = 1; i < line.size() - 1; i++) {

                // soldier of side one
                if (line[i] == '1') {
                    _armyOne.push_back(new Entity('1', i, _battleGround.size() - 1, &_battleGround));
                    _armyOneAlive++;
                }

                // soldier of side two
                else if (line[i] == '2') {
                    _armyTwo.push_back(new Entity('2', i, _battleGround.size() - 1, &_battleGround));
                    _armyTwoAlive++;
                }
            }
        }
    }
    inputFile.close();

    // Shuffling army vectors for randomness
    shuffle(_armyOne.begin(), _armyOne.end(), Duel::RandomEngine);
    shuffle(_armyTwo.begin(), _armyTwo.end(), Duel::RandomEngine);

    /*
        Instead of using two loops for duels of two sides, one loop is used.
        Also, it will ensure that a second side duel is after adding first a side duel.
    */
    int maxSize;
    if (_armyOne.size() > _armyTwo.size()) {
        maxSize = _armyOne.size();
    }
    else {
        maxSize = _armyTwo.size();
    }

    for (int i = 0; i < maxSize; i++) {

        if (i < _armyOne.size()) {
            _duels.push_back(new Duel(_armyOne[i], _armyOne[i]->findTarget(_armyTwo)));
        }

        if (i < _armyTwo.size()) {
            _duels.push_back(new Duel(_armyTwo[i], _armyTwo[i]->findTarget(_armyOne)));
        }
    }

    // Shuffling duel vectors for randomness in fight
    shuffle(_duels.begin(), _duels.end(), Duel::RandomEngine);
}

/*
    Performs the duels until every soldiers of one the sides die.
    Initiates new duels for winner of ended duels.
*/
void Combat::startBattle(unsigned int attackIntervalInMills) {

    _printBattleGround();
    std::chrono::milliseconds duration(attackIntervalInMills);
    int finalWinner = 0;

    while (_armyOneAlive > 0 && _armyTwoAlive > 0) {
        
            for (int i = 0; i < _duels.size(); i++) {

                if (_duels[i] != NULL) {

                    /*
                        If one of the soldiers in duel died in another duel, this duel is deleted.
                        The alive soldier finds new target and initiates a new duel.
                    */
                    if (_duels[i]->isOneDead() || _duels[i]->isTwoDead()) {

                        Entity* alive = nullptr;

                        if (_duels[i]->isOneDead()) { // two is alive
                            alive = _duels[i]->getTarget();
                        }
                        else { // one is alive
                            alive = _duels[i]->getSoldier();
                        }

                        delete _duels[i];
                        _duels[i] = NULL;

                        // determine side of alive soldier and initiate new duel

                        if (alive->getSign() == '1') {
                            _duels[i] = new Duel(alive, alive->findTarget(_armyTwo));
                            i--;
                        }
                        else if (alive->getSign() == '2') {
                            _duels[i] = new Duel(alive, alive->findTarget(_armyOne));
                            i--;
                        }
                    }
                    else {
                        std::this_thread::sleep_for(duration);
                        Entity* winner = _duels[i]->attack();

                        if (winner != nullptr) { // no nullptr means duel ended

                            delete _duels[i];
                            _duels[i] = NULL;

                            // determine side of winner soldier and initiate new duel if not all the soldiers of opposing side died

                            if (winner->getSign() == '1') {

                                _armyTwoAlive--;

                                if (_armyTwoAlive <= 0) { // all the soldiers of opposing died
                                    finalWinner = 1;
                                    break;
                                }

                                _duels[i] = new Duel(winner, winner->findTarget(_armyTwo));
                                i--;
                            }
                            else if (winner->getSign() == '2') {

                                _armyOneAlive--;

                                if (_armyOneAlive <= 0) { // all the soldiers of opposing died
                                    finalWinner = 2;
                                    break;
                                }

                                _duels[i] = new Duel(winner, winner->findTarget(_armyOne));
                                i--;
                            }
                        }
                    }
                    _printBattleGround();
                }
            }
    }
    _printBattleGround();
    std::cout << finalWinner << " won!\n\n";
}

/*
    Just deletes the allocated memory if not already deleted
*/
void Combat::endBattle() {
    for (int i = 0; i < _armyOne.size(); i++) {
        if (_armyOne[i] != NULL) {
            delete _armyOne[i];
            _armyOne[i] = NULL;
        }
    }

    for (int i = 0; i < _armyTwo.size(); i++) {
        if (_armyTwo[i] != NULL) {
            delete _armyTwo[i];
            _armyTwo[i] = NULL;
        }
    }

    for (int i = 0; i < _duels.size(); i++) {
        if (_duels[i] != NULL) {
            delete _duels[i];
            _duels[i] = NULL;
        }
    }
}

void Combat::_printBattleGround() {
    
    static std::string topIndent = std::string(3, '\n');
    static std::string bottomIndent = std::string(3, '\n');

    std::string output = topIndent + "*** Enhanced Console Warfare ***\n\n";
    output += "Space - Pause/Resume\nEsc - Stop and Exit\n\n";
    for (int i = 0; i < _battleGround.size(); i++) {
        output += " " + _battleGround[i] + "\n";
    }
    output += bottomIndent;
    std::cout << output;
}