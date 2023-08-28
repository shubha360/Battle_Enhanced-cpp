#pragma once

#include <vector>
#include <string>

using namespace std;

class Entity {
public:
	static const int ENTITY_STARTING_HEALTH;

	Entity();
	Entity(char sign, int posX, int posY, vector<string>* battleGround);

	Entity* findTarget(vector<Entity*> opponentList);
	void moveTowards(Entity* opponent);
	void takeDamage(int damage);
	void died();

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
	vector<string>* _battleGround;
	Entity* _target;

	int _getDistance(int targetX, int targetY);
	void _moveUp();
	void _moveDown();
	void _moveLeft();
	void _moveRight();
};

