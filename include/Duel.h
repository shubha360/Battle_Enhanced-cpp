#pragma once

#include "Entity.h"

#include <random>

class Duel {
public:
	Duel(Entity* one, Entity* two);

	Entity* attack();
	Entity* getSoldier() { return _soldier; }
	Entity* getTarget() { return _target; }
	bool isOneDead() { return _soldier->isDead(); }
	bool isTwoDead() { return _target->isDead(); }

	static std::mt19937 RandomEngine;

private:
	Entity* _soldier;
	Entity* _target;

	static std::random_device _seed;
};

