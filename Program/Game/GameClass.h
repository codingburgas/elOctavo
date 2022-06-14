#pragma once
#include "Precompile.h"

class Player {
private:

	// init variables

	int* posX;
	int* posY;
	int* hp;
	Sprite spriteMainCharacter;

public:

	// init constructor
	// probable error

	Player(int* posX, int* posY, int* hp, Sprite sprite) : posX(posX), posY(posY), hp(hp), spriteMainCharacter(sprite) {
		updatePos(this->posX, this->posY);
	}

	// update functions

	void updatePos(int* newX, int* newY) {
		this->posX = newX;
		this->posY = newY;
		this->spriteMainCharacter.move(*newX, *newY);
	};

	void changeSprite(Texture* newTexture) {
		this->spriteMainCharacter.setTexture(*newTexture);
	};

	void updateHealth(int* newHp) {
		this->hp = newHp;
	};

	// combat functions

	void takeDamage(int damage) {
		this->hp -= damage;
	};

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
	};

	void changeSprite(Texture* newTexture) {
		this->spriteNpc.setTexture(*newTexture);
	};

	void updateHealth(int* newHp) {
		this->hp = newHp;
	};

	// combat functions

	void takeDamage(int damage) {
		this->hp -= damage;
	};
};