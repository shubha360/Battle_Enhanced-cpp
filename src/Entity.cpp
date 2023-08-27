#include "../include/Entity.h"

const int Entity::ENTITY_STARTING_HEALTH = 100;

Entity::Entity() {
	_sign = ' ';
	_posX = -1;
	_posY = -1;
	_health = ENTITY_STARTING_HEALTH;
	_battleGround = nullptr;
	_opponent = nullptr;
	_dead = false;
}

Entity::Entity(char sign, int posX, int posY, vector<string>* battleGround) {
	_sign = sign;
	_posX = posX;
	_posY = posY;
	_health = ENTITY_STARTING_HEALTH;	
	_battleGround = battleGround;
	_dead = false;
	_opponent = nullptr;
}

Entity* Entity::findTarget(vector<Entity*> opponentList) {
	int currentDistance = INT_MAX;

	for (int i = 0; i < opponentList.size(); i++) {
		if (!opponentList[i]->isDead()) {

			Entity* current = opponentList[i];

			int distance = _getDistance(current->getPosX(), current->getPosY());
			if (distance < currentDistance) {
				currentDistance = distance;
				_opponent = current;
			}
		}
	}	
	return _opponent;
}

void Entity::moveTowards(Entity* opponent) {
	if (opponent->getPosY() > _posY) {
		if ((*_battleGround)[_posY + 1][_posX] == ' ') {
			_moveDown();
		}
		else {
			if (opponent->getPosX() > _posX) {
				if ((*_battleGround)[_posY][_posX + 1] == ' ') {
					_moveRight();
				}
			}
			else if (opponent->getPosX() < _posX) {
				if ((*_battleGround)[_posY][_posX - 1] == ' ') {
					_moveLeft();
				}
			}
		}
	}
	else if (opponent->getPosY() < _posY) {
		if ((*_battleGround)[_posY - 1][_posX] == ' ') {
			_moveUp();
		}
		else {
			if (opponent->getPosX() > _posX) {
				if ((*_battleGround)[_posY][_posX + 1] == ' ') {
					_moveRight();
				}
			}
			else if (opponent->getPosX() < _posX) {
				if ((*_battleGround)[_posY][_posX - 1] == ' ') {
					_moveLeft();
				}
			}
		}
	}
	else {
		if (opponent->getPosX() > _posX) {
			if ((*_battleGround)[_posY][_posX + 1] == ' ') {
				_moveRight();
			}
		}
		else if (opponent->getPosX() < _posX) {
			if ((*_battleGround)[_posY][_posX - 1] == ' ') {
				_moveLeft();
			}
		}
	}
}

void Entity::takeDamage(int damage) {
	_health -= damage;
}

void Entity::died() {
	_dead = true;
	(*_battleGround)[_posY][_posX] = ' ';
	_sign = ' ';
	_posX = 0;
	_posY = 0;
	_opponent = nullptr;
}

int Entity::_getDistance(int targetX, int targetY) {
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