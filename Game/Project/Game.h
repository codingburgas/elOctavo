#pragma once
#include "Project.h"
//wrapper class

class Game
{
private:

	//variables
	
	//window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	//Private functions
	void variables();
	void windowInIt();
	 
public:

	//constructors and destructors
	Game();
	virtual ~Game();

	//variables
	const bool getWinwowIsOpen();

	//functions

	void update();
	void render();
};

