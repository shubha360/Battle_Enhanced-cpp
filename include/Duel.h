#pragma once

#include "Entity.h"

#include <random>

class Duel {
public:
	Duel();
	Duel(Entity* one, Entity* two);

	Entity* attack();
	Entity* getSoldier() { return _soldier; }
	Entity* getTarget() { return _target; }
	bool isOneDead() { return _soldier->isDead(); }
	bool isTwoDead() { return _target->isDead(); }

private:
	Entity* _soldier;
	Entity* _target;

	// variables to randomize
	static default_random_engine _randomEngine;
	static uniform_int_distribution<int> _nextTurnGenerator;
	static uniform_int_distribution<int> _strikeIntensityGenerator;
};

