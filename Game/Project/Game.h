#pragma once
#include "Project.h"
class Game
{
	private:

		//variables
		RenderWindow window;
		int keyTime;
		Event ev;
		RectangleShape square;

	public:
		
		void setVars(RenderWindow window, int keyTime, Event ev, RectangleShape square)
		{
			//this->window = window;
			this->keyTime = keyTime;
			this->ev = ev;
			this->square = square;
		}

};

