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
	Sprite pSprite;

public:

	void setPublicVariables(float posX, float posY, int hp, Sprite pSprite)
	{
		this->posX = posX;
		this->posY = posY;
		this->hp = hp;
		this->pSprite = pSprite;
		this->pMoved = false;
	}

	void setValues()
	{
		this->pSprite.setPosition(this->posX, this->posY);
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

	void updatePos(float moveX, float moveY) {
		this->pSprite.move(moveX, moveY);

		this->posX = pSprite.getPosition().x;
		this->posY = pSprite.getPosition().y;
	}

	void changeSprite(Texture* newTexture) {
		this->pSprite.setTexture(*newTexture);
	}

	void updateHealth(int newHp) {
		this->hp = newHp;
	}

	void draw(RenderWindow& window) {
		window.draw(pSprite);
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