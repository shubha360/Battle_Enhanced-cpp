#pragma once

#include <vector>
#include <string>

class Entity {
public:
	static const int ENTITY_STARTING_HEALTH;

	Entity();
	Entity(char sign, int posX, int posY, std::vector<std::string>* battleGround);

	Entity* findTarget(std::vector<Entity*> opponentList); // find new target
	void moveTowards(Entity* target); // move toward target
	void takeDamage(int damage); // take damage and decrease health
	void died(); // this entity died

	int getDistance(int targetX, int targetY); // find target distance

	char getSign() { return _sign; }
	int getPosX() { return _posX; }
	int getPosY() { return _posY; }
	int getHealth() { return _health; }
	bool isDead() { return _dead; }
	Entity* getOpponent() { return _target; }

private:
	char _sign;
	int _posX, _posY;
	int _health;
	bool _dead;
	std::vector<std::string>* _battleGround;
	Entity* _target;

	// functions to to move entity
	void _moveUp();
	void _moveDown();
	void _moveLeft();
	void _moveRight();
};

