#include "../include/Duel.h"

Duel::Duel() {
	_soldier = nullptr;
	_target = nullptr;
}

Duel::Duel(Entity* one, Entity* two) {
	_soldier = one;
	_target = two;
}

/*
	If target is not in range, soldier moves towards the target.
	Fight each other if the two soldiers are in vertically or horizontally adjacent cells.
	Which entity will strike and strike intensity are determined randomly.
	Returns the memory location to winner entity.
*/
Entity* Duel::attack() {

	static default_random_engine randomEngine = default_random_engine(time(0));
	
	static uniform_int_distribution<int> nextTurnGenerator = uniform_int_distribution<int>(1, 2); // 1 - soldier strike, 2 - target strike
	static uniform_int_distribution<int> strikeIntensityGenerator = uniform_int_distribution<int>(1, 5);

	Entity* winner = nullptr;
	int distance = _soldier->getDistance(_target->getPosX(), _target->getPosY());

	if (distance == 1) { // target in range
		int nextTurn = nextTurnGenerator(randomEngine);
		int attackIntensity = strikeIntensityGenerator(randomEngine);

		if (nextTurn == 1) { // soldier strike
			_target->takeDamage(20 * attackIntensity);

			// target died
			if (_target->getHealth() <= 0) {
				winner = _soldier;
				_target->died();
			}
		}
		else { // target strike
			_soldier->takeDamage(20 * attackIntensity);

			// soldier died
			if (_soldier->getHealth() <= 0) {
				winner = _target;
				_soldier->died();
			}
		}
	}
	else { // target not in range
		_soldier->moveTowards(_target);
	}
	return winner;
}