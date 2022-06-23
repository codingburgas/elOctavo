#include "../Header files/Precompile.h";
#include "../Header files/Additional Functions.h";


void changeFPS(int FPS, RenderWindow& window)
{
	window.setFramerateLimit(FPS);
}

void addIcon(RenderWindow& window)
{
	Image icon;
	
	if (!icon.loadFromFile("../Images and fonts/Icon.png"))
	{
		cout << "Error";
	}

	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}