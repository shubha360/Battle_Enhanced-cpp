#include "../include/Combat.h"

Combat::Combat() {
    _sideOneAlive = 0;
    _sideTwoAlive = 0;
    _topIndent = string(5, '\n');
}

Combat::~Combat() {
    endBattle();
}

void Combat::init() {    
    ifstream inputFile;

    inputFile.open("files/test.txt");
    if (inputFile.fail()) {
        perror("files/test.txt");
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

void Combat::startBattle() {
    cout << "*** Legends of Console Warfare ***\n\n";

    while (_sideOneAlive > 0 && _sideTwoAlive > 0) {
        
        printBattleGround();

        for (int i = 0; i < _duels.size(); i++) {
            
            if (!_duels[i]->isDuelEnded()) {
                Entity* winner = _duels[i]->attack();

                if (winner != nullptr) {
                    if (winner->getSign() == '1') {
                        _sideTwoAlive--;
                        _duels.push_back(new Duel(winner, winner->findTarget(_sideTwo)));
                    }
                    else if (winner->getSign() == '2') {
                        _duels.push_back(new Duel(winner, winner->findTarget(_sideOne)));
                        _sideOneAlive--;
                    }
                }
                
                if (_sideOneAlive == 0 || _sideTwoAlive == 0) {
                    break;
                }
            }
        }
    }
    printBattleGround();
}

void Combat::endBattle() {
    for (Entity* i : _sideOne)
        delete i;

    for (Entity* i : _sideTwo)
        delete i;

    for (Duel* i : _duels)
        delete i;
}

void Combat::printBattleGround() {
    string output = _topIndent;
    for (int i = 0; i < _battleGround.size(); i++) {
        output += " " + _battleGround[i] + "\n";
    }

    //output += "\n" + to_string(_sideOneAlive) + "\n" + to_string(_sideTwoAlive) + "\n" + to_string(_duels.size()) + "\n\n";

    cout << output;
}