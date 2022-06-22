#pragma once

bool checkCollideWithGround(RectangleShape& body);

void moveCharacter(int& keyTime, RenderWindow& window);

void moveCameraFirstStage(string direction, Sprite& image);

void moveCameraSecondStage(string direction, Sprite& image);

void setVars();

void setup(RenderWindow& window);

bool checkCollideWithHypotenuse(RectangleShape& body);

bool checkCollideWithRamp(RectangleShape& body);
