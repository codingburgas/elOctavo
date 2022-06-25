#pragma once
#include "Precompile.h"

void changeFPS(int FPS, RenderWindow& window);

void addIcon(RenderWindow& window);

void textAnimation(Clock clockLetter, Clock clockWord, Clock clockSentence, float timeLetter, float timeWord, float timeSentence);

extern Clock clockLetter, clockWord, clockSentence;

extern float timeLetter;
extern float timeWord;
extern float timeSentence;