#pragma once

bool checkCollideWithGround(RectangleShape& body);

void setVars();

void setup(RenderWindow& window);

bool checkCollideWithRamp(RectangleShape& body);

class Block {
    public:
        RectangleShape hitbox;
        Block(Vector2f pos, Vector2f size);

        //~Block();

        void drawHitbox(RenderWindow& window);

        bool checkForCollision(RectangleShape& body);
};