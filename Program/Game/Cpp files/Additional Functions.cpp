#include "../Header files/Precompile.h";
#include "../Header files/Additional Functions.h";

namespace variables
{
	Texture backstoryTexture;
	Sprite backstoryImage;
}

using namespace variables;

void changeFPS(int FPS, RenderWindow& window)
{
	window.setFramerateLimit(FPS);
}

void addIcon(RenderWindow& window)
{
	Image icon;
	
	if (!icon.loadFromFile("../Images and fonts/Icon (2).png"))
	{
		cout << "Error";
	}

	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

void backstory()
{
	string textBackstoryOne = "Hello friend!\nI'm a kurabirov and I'm here to tell you my story.\n Some time ago I was a professional boxer and I was very successful in that.\nWhen cryptocurrencies came out, I really liked them and started studying them. \nAnyway, because I knew how the market works,\nit was time to test my knowledge and bought stoshevcoin and staichocoin.\nBut things went wrong and these two cryptocurrencies collapsed.\nA lot of people have become attached to the propaganda that this will be\n the currency of the future and we have lost all our money. Anyway, I became homeless.\nOne day, three costumed men abducted me in a van and put on a mask so I couldn't see. After a while,\n they stopped the van, removed my mask, and I was in front of a mansion\nIt turned out that the boss of the turkish mafia lives here(he also has a telsa). He wanted me to place an order for him. Without telling me much, I agreed and here I am now.";

	int i = 0;
	while (textBackstoryOne[i] != '\0')
	{
		cout << textBackstoryOne[i];
		Sleep(50);
		i++;
	};
}
