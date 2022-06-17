#pragma once
#include "Precompile.h"

class Player {
private:

	// init variables

	float posX;
	float posY;
	int hp;
	int pSC;
	bool pMoved;
	float totalTime;
	float switchTime;
	Vector2u imageCount;
	Vector2u currentImage;

public:
	IntRect uvRect;

	Player(Texture* texture, Vector2u imageCount, float switchTime);
	~Player();

	void update(int row, float deltaTime);

	void setPublicVariables(float posX, float posY, int hp)
	{
		this->posX = posX;
		this->posY = posY;
		this->hp = hp;
		this->pMoved = false;
	}

	// misc functions

	float getPos(char cord) {
		if (cord == 'x') {
			return this->posX;
		}
		else {
			return this->posY;
		}
	}

	bool getMoved() {
		return this->pMoved;
	}


	// update functions

	void updateHealth(int newHp) {
		this->hp = newHp;
	}


	// combat functions

	void takeDamage(int damage) {
		this->hp -= damage;
	}
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