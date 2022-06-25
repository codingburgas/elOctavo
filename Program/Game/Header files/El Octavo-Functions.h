#pragma once
#include "Precompile.h"

bool checkCollideWithGround(RectangleShape& body);

void setVars();

void setup(RenderWindow& window);

bool checkCollideWithRamp(RectangleShape& body);

class CollisionBlock {
public:
    RectangleShape hitbox;

    CollisionBlock(Vector2f pos, Vector2f size);

    ~CollisionBlock();

    void drawHitbox(RenderWindow& window);

    bool checkForCollision(RectangleShape& body);
};

class Npc {
private:
    
    // build variables
    float totalTime;
    float switchTime;
    
    string name;
    string nestashev = "NESTASHEV";

    Vector2u imageCount;
    Vector2u currentImage;

    // movement variables
    unsigned int row;
    float speed;
    bool faceLeft;

    float distance;

public:
    IntRect uvRect;
    RectangleShape body;
    Vector2f velocity;

    Npc(Texture* texture, Vector2u imageCount, float switchTime, float speed, string name);
    ~Npc();

    void draw(RenderWindow& window);
    void moveX(float amount);
    void update(int row, float deltaTime, bool faceLeft);
    bool moveTo(float x, float deltaTime);
};