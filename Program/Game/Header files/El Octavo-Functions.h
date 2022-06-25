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

    float distance;
    int posIndex;

    Clock npcClock; 
    Time npcPreviousTime; 
    Time npcCurrentTime;

    bool reset;


public:
    bool faceLeft;
    IntRect uvRect;
    RectangleShape body;
    Vector2f velocity;
    bool delay;

    Npc(Texture* texture, Vector2u imageCount, float switchTime, float speed, string name);
    ~Npc();

    void draw(RenderWindow& window);
    void moveX(float amount);
    void update(int row, float deltaTime, bool delay);
    void moveTo(float pos[], float deltaTime, bool& done, bool& faceLeft);
};