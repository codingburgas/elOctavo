#include "../Header files/Precompile.h"
#include "../Header files/El Octavo-Functions.h";
#include "../Header files/Menu.h";

int main()
{
	RenderWindow window(VideoMode(1280, 720), "The legend of Kurabirov", sf::Style::Titlebar | sf::Style::Close);

	setupMenu(window);
}

