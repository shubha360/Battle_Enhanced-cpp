#pragma once

class Entity {
public:
	static const int ENTITY_STARTING_HEALTH;

	Entity();
	Entity(char sign, int posX, int posY);

	char getSign() { return _sign; }
	int getPosX() { return _posX; }
	int getPosY() { return _posY; }
	int getHealth() { return _health; }
	bool isDead() { return dead; }

	void moveUp();
	void movDown();
	void moveLeft();
	void moveRight();

private:
	char _sign;
	int _posX, _posY;
	int _health;
	bool dead;
};

