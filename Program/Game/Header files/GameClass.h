#pragma once
#include "Precompile.h"

class Player {
private:

	// build variables
	float totalTime;
	float switchTime;
	Vector2u imageCount;
	Vector2u currentImage;

	// movement variables
	RectangleShape body;
	unsigned int row;
	float speed;
	bool faceLeft;

public:
	IntRect uvRect;

	Player(Texture* texture, Vector2u imageCount, float switchTime, float speed);
	~Player();

	// build functions
	void update(int row, float deltaTime, bool faceLeft);

	//movement functions
	void updateMovement(float deltaTime);
	void draw(RenderWindow& window);
};

class Npc {
private:

	// init variables

	int* posX;
	int* posY;

	int* hp;
	Sprite spriteNpc;

public:

	// init constructor
	// probable error

	Npc(int* posX, int* posY, int* hp, Sprite sprite) : posX(posX), posY(posY), hp(hp), spriteNpc(sprite) {
		updatePos(this->posX, this->posY);
	}

	// update functions

	void updatePos(int* newX, int* newY) {
		this->posX = newX;
		this->posY = newY;
		this->spriteNpc.move(*newX, *newY);
	}

	void changeSprite(Texture* newTexture) {
		this->spriteNpc.setTexture(*newTexture);
	}

	void updateHealth(int* newHp) {
		this->hp = newHp;
	}

	// combat functions

	void takeDamage(int damage) {
		this->hp -= damage;
	}
};