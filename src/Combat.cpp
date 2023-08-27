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
                if (line[i] == '1') {
                    _sideOne.push_back(new Entity('1', i, _battleGround.size() - 1, &_battleGround));
                    _sideOneAlive++;
                }
                else if (line[i] == '2') {
                    _sideTwo.push_back(new Entity('2', i, _battleGround.size() - 1, &_battleGround));
                    _sideTwoAlive++;
                }
            }
        }
    }

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

void Combat::startBattle(int makeAttackSlowInMilli) {
    printBattleGround();
    chrono::milliseconds duration(makeAttackSlowInMilli);
    int finalWinner;

    while (_sideOneAlive > 0 && _sideTwoAlive > 0) {
       
        for (int i = 0; i < _duels.size(); i++) {
            
            if (_duels[i] != NULL) {

                if (_duels[i]->isOneDead() || _duels[i]->isTwoDead()) {
                    
                    Entity* alive = nullptr;

                    if (_duels[i]->isOneDead()) {
                        alive = _duels[i]->getTwo();
                    }
                    else {
                        alive = _duels[i]->getOne();
                    }

                    delete _duels[i];
                    _duels[i] = NULL;

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

                    if (winner != nullptr) {

                        delete _duels[i];
                        _duels[i] = NULL;

                        if (winner->getSign() == '1') {

                            _sideTwoAlive--;

                            if (_sideTwoAlive <= 0) {
                                finalWinner = 1;
                                break;
                            }

                            _duels[i] = new Duel(winner, winner->findTarget(_sideTwo));
                            i--;
                        }
                        else if (winner->getSign() == '2') {

                            _sideOneAlive--;

                            if (_sideOneAlive <= 0) {
                                finalWinner = 2;
                                break;
                            }

                            _duels[i] = new Duel(winner, winner->findTarget(_sideOne));
                            i--;
                        }
                    }
                }
                printBattleGround();
            }
        }
    }
    printBattleGround();
    cout << finalWinner << " won!\n\n";
}

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

void Combat::printBattleGround() {
    string output = _topIndent + "*** Enhanced Console Warfare ***\n\n";
    for (int i = 0; i < _battleGround.size(); i++) {
        output += " " + _battleGround[i] + "\n";
    }
    output += _bottomIndent;
    //output += "\n" + to_string(_sideOneAlive) + "\n" + to_string(_sideTwoAlive) + "\n" + to_string(_duels.size()) + "\n\n";
    cout << output;
}