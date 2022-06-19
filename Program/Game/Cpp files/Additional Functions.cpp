#include "../Header files/Precompile.h";
#include "../Header files/Additional Functions.h";

namespace variables {
	/*int FPS;
	Font font;
	Text fpsCounter;*/
}

using namespace variables;

void setupFont() {
	/*font.loadFromFile("../Images and fonts/Fonts/Header font.ttf");
	fpsCounter.setFont(font);
	fpsCounter.setCharacterSize(24);*/
}

void changeFPS(int FPS, RenderWindow& window)
{
	window.setFramerateLimit(FPS);
}


void showFPS(int FPS, RenderWindow& window)
{
	/*fpsCounter.setString(to_string(FPS));
	fpsCounter.setPosition(1100, 70);*/
}

//bool turnAudio()
//{
//	 code for audio toggle
//}

void addIcon(RenderWindow& window)
{
	auto icon = Image{};

	if (!icon.loadFromFile("../Images and fonts/Icon.png"))
	{
		cout << "Error";
	}

	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}