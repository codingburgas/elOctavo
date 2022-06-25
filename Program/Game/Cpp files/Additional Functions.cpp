#include "../Header files/Precompile.h";
#include "../Header files/Additional Functions.h";

Clock clockLetter, clockWord, clockSentence;

float timeLetter = 0.1;
float timeWord = 0.4;
float timeSentence = 1;

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

void textAnimation(Clock clockLetter, Clock clockWord, Clock clockSentence, float timeLetter, float timeWord, float timeSentence)
{
	string text = "Zabirov bie hora za pari. Da vqrno e!";
	
	for (int i = 0; i < text.length(); i++)
	{
		if (clockLetter.getElapsedTime().asSeconds() >= timeLetter)
		{
			cout << text[i];
		}

		else if (clockWord.getElapsedTime().asSeconds() >= timeWord && text[i] == ' ')
		{
			cout << text[i];
		}

		else if (clockSentence.getElapsedTime().asSeconds() >= timeSentence && text[i] == '.' && text[i] == ' ')
		{
			cout << text[i];
		}
	}
	
}