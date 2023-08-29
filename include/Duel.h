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
};

