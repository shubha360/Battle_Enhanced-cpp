#include "../include/Duel.h"

default_random_engine Duel::_randomEngine = default_random_engine(time(0));
uniform_int_distribution<int> Duel::_nextTurnGenerator = uniform_int_distribution<int>(1, 2);
uniform_int_distribution<int> Duel::_attackIntensityGenerator = uniform_int_distribution<int>(1, 5);

Duel::Duel() {
	_one = nullptr;
	_two = nullptr;
	_duelEnded = false;
}

Duel::Duel(Entity* one, Entity* two) {
	_one = one;
	_two = two;
	_duelEnded = false;
}

Entity* Duel::attack() {

	Entity* winner = nullptr;

	int distance = _getEntityDistance();

	if (distance == 1) {
		int nextTurn = _nextTurnGenerator(_randomEngine);
		int attackIntensity = _attackIntensityGenerator(_randomEngine);

		if (nextTurn == 1) {
			_two->takeDamage(20 * attackIntensity);
			
			// opponent died
			if (_two->getHealth() <= 0) {
				winner = _one;
				_two->died();
				_duelEnded = true;
			}
		}
		else {
			_one->takeDamage(20 * attackIntensity);

			// soldier died
			if (_one->getHealth() <= 0) {
				winner = _two;
				_one->died();
				_duelEnded = true;
			}
		}
	}
	else {
		_one->moveTowards(_two);
	}
	return winner;
}

int Duel::_getEntityDistance() {
	int disX = _one->getPosX() - _two->getPosX();
	int disY = _one->getPosY() - _two->getPosY();

	return (disX * disX) + (disY * disY);
}