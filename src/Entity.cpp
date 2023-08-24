#include "../include/Entity.h"

const int Entity::ENTITY_STARTING_HEALTH = 100;

Entity::Entity() {}

Entity::Entity(char sign, int posX, int posY) {
	_sign = sign;
	_posX = posX;
	_posY = posY;
	_health = ENTITY_STARTING_HEALTH;
	dead = false;
}

void Entity::moveUp() {
	_posY--;
}

void Entity::movDown() {
	_posY++;
}

void Entity::moveLeft() {
	_posX--;
}

void Entity::moveRight() {
	_posX++;
}