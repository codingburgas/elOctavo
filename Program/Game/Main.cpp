#include "Precompile.h"
#include "El Octavo-Functions.h";
#include "Menu.h";

int main()
{
	RenderWindow window(VideoMode(1280, 720), "The legend of Kurabirov", sf::Style::Titlebar | sf::Style::Close);
	setupMenu(window);
}

