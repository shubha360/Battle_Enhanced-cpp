#include "../include/Combat.h"

Combat::Combat() {
    _sideOneAlive = 0;
    _sideTwoAlive = 0;
    _topIndent = string(3, '\n');
    _bottomIndent = string(3, '\n');
}

Combat::~Combat() {
    endBattle();
}

/*
    Mainly reads the battle ground and soldiers from file and initializes the starting duels
*/
void Combat::init(string combatFile) {    
    ifstream inputFile;

    inputFile.open(combatFile);
    if (inputFile.fail()) {
        perror(combatFile.c_str());
        return;
    }

    string line;

    while (getline(inputFile, line)) {
        _battleGround.push_back(line);

        if (line[0] == '|') {
            for (int i = 1; i < line.size() - 1; i++) {

                // soldier of side one
                if (line[i] == '1') {
                    _sideOne.push_back(new Entity('1', i, _battleGround.size() - 1, &_battleGround));
                    _sideOneAlive++;
                }

                // soldier of side two
                else if (line[i] == '2') {
                    _sideTwo.push_back(new Entity('2', i, _battleGround.size() - 1, &_battleGround));
                    _sideTwoAlive++;
                }
            }
        }
    }
    inputFile.close();

    /*
        Instead of using two loops for duels of two sides, one loop is used.
        Also, it will ensure that a second side duel is after adding first a side duel.
    */
    int maxSize;
    if (_sideOne.size() > _sideTwo.size()) {
        maxSize = _sideOne.size();
    }
    else {
        maxSize = _sideTwo.size();
    }

    for (int i = 0; i < maxSize; i++) {

        if (i < _sideOne.size()) {
            _duels.push_back(new Duel(_sideOne[i], _sideOne[i]->findTarget(_sideTwo)));
        }

        if (i < _sideTwo.size()) {
            _duels.push_back(new Duel(_sideTwo[i], _sideTwo[i]->findTarget(_sideOne)));
        }
    }
}

/*
    Performs the duels until every soldiers of one the sides die.
    Initiates new duels for winner of ended duels.
*/
void Combat::startBattle(unsigned int attackIntervalInMills) {

    _printBattleGround();
    chrono::milliseconds duration(attackIntervalInMills);
    int finalWinner = 0;

    while (_sideOneAlive > 0 && _sideTwoAlive > 0) {
       
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
                        _duels[i] = new Duel(alive, alive->findTarget(_sideTwo));
                        i--;
                    }
                    else if (alive->getSign() == '2') {
                        _duels[i] = new Duel(alive, alive->findTarget(_sideOne));
                        i--;
                    }
                }
                else {
                    this_thread::sleep_for(duration);
                    Entity* winner = _duels[i]->attack();

                    if (winner != nullptr) { // no nullptr means duel ended

                        delete _duels[i];
                        _duels[i] = NULL;

                        // determine side of winner soldier and initiate new duel if not all the soldiers of opposing side died

                        if (winner->getSign() == '1') {

                            _sideTwoAlive--;

                            if (_sideTwoAlive <= 0) { // all the soldiers of opposing died
                                finalWinner = 1;
                                break;
                            }

                            _duels[i] = new Duel(winner, winner->findTarget(_sideTwo));
                            i--;
                        }
                        else if (winner->getSign() == '2') {

                            _sideOneAlive--;

                            if (_sideOneAlive <= 0) { // all the soldiers of opposing died
                                finalWinner = 2;
                                break;
                            }

                            _duels[i] = new Duel(winner, winner->findTarget(_sideOne));
                            i--;
                        }
                    }
                }
                _printBattleGround();
            }
        }
    }
    _printBattleGround();
    cout << finalWinner << " won!\n\n";
}

/*
    Just deletes the allocated memory if not already deleted
*/
void Combat::endBattle() {
    for (int i = 0; i < _sideOne.size(); i++) {
        if (_sideOne[i] != NULL) {
            delete _sideOne[i];
            _sideOne[i] = NULL;
        }
    }

    for (int i = 0; i < _sideTwo.size(); i++) {
        if (_sideTwo[i] != NULL) {
            delete _sideTwo[i];
            _sideTwo[i] = NULL;
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
    string output = _topIndent + "*** Enhanced Console Warfare ***\n\n";
    for (int i = 0; i < _battleGround.size(); i++) {
        output += " " + _battleGround[i] + "\n";
    }
    output += _bottomIndent;
    cout << output;
}