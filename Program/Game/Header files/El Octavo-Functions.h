#pragma once
#include "Precompile.h"

bool checkCollideWithGround(RectangleShape& body);

void setVars();

void setup(RenderWindow& window);

bool checkCollideWithRamp(RectangleShape& body);

class collisionBlock {
public:
    RectangleShape hitbox;

    collisionBlock(Vector2f pos, Vector2f size);

    ~collisionBlock();

    void drawHitbox(RenderWindow& window);

    bool checkForCollision(RectangleShape& body);
};