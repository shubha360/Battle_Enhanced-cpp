#pragma once

#include "Entity.h"

#include <random>

class Duel {
public:
	Duel();
	Duel(Entity* one, Entity* two);

	Entity* attack();
	int getEntityDistance();
	bool isDuelEnded() { return _duelEnded; }

private:
	Entity* _one;
	Entity* _two;
	bool _duelEnded;

	static default_random_engine _randomEngine;
	static uniform_int_distribution<int> _nextTurnGenerator;
	static uniform_int_distribution<int> _attackIntensityGenerator;
};

