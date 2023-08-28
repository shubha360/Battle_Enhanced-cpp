#include "../include/Entity.h"

const int Entity::ENTITY_STARTING_HEALTH = 100;

Entity::Entity() {
	_sign = ' ';
	_posX = -1;
	_posY = -1;
	_health = ENTITY_STARTING_HEALTH;
	_battleGround = nullptr;
	_target = nullptr;
	_dead = false;
}

Entity::Entity(char sign, int posX, int posY, vector<string>* battleGround) {
	_sign = sign;
	_posX = posX;
	_posY = posY;
	_health = ENTITY_STARTING_HEALTH;	
	_battleGround = battleGround;
	_dead = false;
	_target = nullptr;
}
/*
	Finds the closest target from opponent side and return it.
*/
Entity* Entity::findTarget(vector<Entity*> opponentList) {
	int currentDistance = INT_MAX;

	for (int i = 0; i < opponentList.size(); i++) {
		if (!opponentList[i]->isDead()) {

			Entity* current = opponentList[i];
			int distance = getDistance(current->getPosX(), current->getPosY());

			if (distance < currentDistance) {
				currentDistance = distance;
				_target = current;
			}
		}
	}	
	return _target;
}

/*
	Moves towards the target.
	First tries to move vertically to the same row as the target. If can't tries to move one cell horizontally to the direction of target's column.
	Starts moving horizontally once in the same row as the target.
*/
void Entity::moveTowards(Entity* target) {

	// target is below
	if (target->getPosY() > _posY) {
		if ((*_battleGround)[_posY + 1][_posX] == ' ') { // move down if possible
			_moveDown();
		}
		else { // can't move down
			// target is on right
			if (target->getPosX() > _posX) {
				if ((*_battleGround)[_posY][_posX + 1] == ' ') { // move right if possible
					_moveRight();
				}
			}
			// target is on left
			else if (target->getPosX() < _posX) {
				if ((*_battleGround)[_posY][_posX - 1] == ' ') { // move left if possible
					_moveLeft();
				}
			}
		}
	}
	// target is above
	else if (target->getPosY() < _posY) {
		if ((*_battleGround)[_posY - 1][_posX] == ' ') { // move up if possible
			_moveUp();
		}
		else { // can't move up
			// target is on right
			if (target->getPosX() > _posX) {
				if ((*_battleGround)[_posY][_posX + 1] == ' ') { // move right if possible
					_moveRight();
				}
			}
			// target is on left
			else if (target->getPosX() < _posX) {
				if ((*_battleGround)[_posY][_posX - 1] == ' ') { // move left if possible
					_moveLeft();
				}
			}
		}
	}
	// in the same row as target
	else {
		// target is on right
		if (target->getPosX() > _posX) {
			if ((*_battleGround)[_posY][_posX + 1] == ' ') { // move right if possible
				_moveRight();
			}
		}
		// target is on left
		else if (target->getPosX() < _posX) {
			if ((*_battleGround)[_posY][_posX - 1] == ' ') { // move left if possible
				_moveLeft();
			}
		}
	}
}

void Entity::takeDamage(int damage) {
	_health -= damage;
}

void Entity::died() {
	(*_battleGround)[_posY][_posX] = ' ';
	_dead = true;
	_sign = ' ';
	_posX = 0;
	_posY = 0;
	_target = nullptr;
}

/*
	According to pythagorean theorem, distance = square root of (horizontal distance squared + vertical distance squared)
	The square root part is left out. Because it will add extra overhead and leaving it is fine for this purpose.
	If x > y then x^2 > y^2
*/
int Entity::getDistance(int targetX, int targetY) {
	int  disX = _posX - targetX;
	int disY = _posY - targetY;

	return (disX * disX) + (disY * disY);
}

void Entity::_moveUp() {
	(*_battleGround)[_posY][_posX] = ' ';
	_posY--;
	(*_battleGround)[_posY][_posX] = _sign;
}

void Entity::_moveDown() {
	(*_battleGround)[_posY][_posX] = ' ';
	_posY++;
	(*_battleGround)[_posY][_posX] = _sign;
}

void Entity::_moveLeft() {
	(*_battleGround)[_posY][_posX] = ' ';
	_posX--;
	(*_battleGround)[_posY][_posX] = _sign;
}

void Entity::_moveRight() {
	(*_battleGround)[_posY][_posX] = ' ';
	_posX++;
	(*_battleGround)[_posY][_posX] = _sign;
}