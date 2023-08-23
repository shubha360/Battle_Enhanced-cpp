#include "Combat.h"

Combat::Combat() {}

void Combat::init() {
    cout << "*** Legends of Console Warfare ***\n\n";

    _firstSideName = _takeStringInput("Enter the name of first side: ");
    _firstSideSign = _takeCharInput("Enter the sign of " + _firstSideName + ": ");
    _firstSideEntities = _takeIntInput("Enter the number of entities of " + _firstSideName + ": ");

    cout << "\n\n";

    _secondSideName = _takeStringInput("Enter the name of second side: ");
    _secondSideSign = _takeCharInput("Enter the sign of " + _secondSideName + ": ");
    _secondSideEntities = _takeIntInput("Enter the number of entities of " + _secondSideName + ": ");
}

string Combat::_takeStringInput(string prompt) {
    string input;

    do {
        cout << prompt;
        cin >> input;

        if (input == _firstSideName) {
            cout << "Name already taken! Please choose another name.\n\n";
        }
        /*
        else if (input == "") {
            cout << "Can't take empty name!Please choose another name.\n\n";
        }*/
        else {
            break;
        }
    } while(true);
    return input;
}

char Combat::_takeCharInput(string prompt) {
    char input;

    do {
        cout << prompt;
        input = _getch();
        cout << input;
        cout << "\n";

        if (input == _firstSideSign) {
            cout << "Sign already taken! Please choose another sign.\n\n";
        }
        else if (input < 33 || input > 126) {
            cout << "Can't take this!Please choose another sign.\n\n";
        }
        else {
            break;
        }
    } while(true);
    return input;
}

int Combat::_takeIntInput(string prompt) {
    int input;

    do {
        cout << prompt;
        cin >> input;

        if (input < 1) {
            cout << "Numbers of entities can't be less than 1!\n\n";
        }
        else {
            break;
        }
    } while(true);
    return input;
}
