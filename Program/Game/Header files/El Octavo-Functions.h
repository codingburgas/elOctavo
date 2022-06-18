#pragma once

bool checkCollideWithGround(RectangleShape& body);

void moveCharacter(int& keyTime, RenderWindow& window);

void moveCamera(string direction, Sprite& image);

void setVars();

void setup(RenderWindow& window);