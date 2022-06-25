#include "../Header files/Precompile.h"
#include "../Header files/Menu.h"
#include "../Header files/El Octavo-Functions.h"
#include "../Header files/Additional Functions.h"

bool audioToggle = true;

namespace variables {
    Event evMenu;

    Texture textureMenu;
    Sprite bgImageMenu;

    Music music;

    Texture texture;
}

using namespace variables;

void setupMenu(RenderWindow& window);

void setupVars(RenderWindow& window)
{
    if (!music.openFromFile("../Audios/Main.ogg"))
    {
        cout << "Error" << endl;
    }

    if (audioToggle)
    {
        music.play();
    }
    else {
        cout << "";
    }

    addIcon(window);
    music.setLoop(true);
}

void optionMenu(Event& ev, Texture texture, RenderWindow& window)
{
    texture.loadFromFile("../Images and fonts/Bg/TrueFullOptionsMenuSoundOn.png");

    while (true)
    {
        Sprite sprite(texture);

        while (window.pollEvent(ev))
        {
            switch (ev.type)
            {
            case Event::MouseButtonPressed:
            {
                switch (ev.key.code)
                {
                case Mouse::Left:
                {
                    if ((ev.mouseButton.x >= 594 && ev.mouseButton.x <= 629) && (ev.mouseButton.y >= 386 && ev.mouseButton.y <= 421))
                    {
                        texture.loadFromFile("../Images and fonts/Bg/TrueFullOptionsMenuSoundOn.png");
                        audioToggle = true;
                    }

                    else if ((ev.mouseButton.x >= 648 && ev.mouseButton.x <= 683) && (ev.mouseButton.y >= 386 && ev.mouseButton.y <= 421))
                    {
                        texture.loadFromFile("../Images and fonts/Bg/TrueFullOptionsMenuSoundOff.png");
                        audioToggle = false;
                    }

                    else if ((ev.mouseButton.x >= 875 && ev.mouseButton.x <= 962) && (ev.mouseButton.y >= 508 && ev.mouseButton.y <= 541))
                    {
                        setupMenu(window);
                    }
                    break;
                }
                break;
                }
            }
            }
        }
        window.draw(sprite);
        window.display();
    }
}

void setupMenu(RenderWindow& window)
{
    setupVars(window);

    textureMenu.loadFromFile("../Images and fonts/Bg/Menu.png");
    bgImageMenu.setTexture(textureMenu);;
    bgImageMenu.setOrigin(1280 / 2, 720 / 2);
    bgImageMenu.setPosition(window.getSize().x / 2, window.getSize().y / 2);

    while (window.isOpen())
    {
        while (window.pollEvent(evMenu))
        {
            switch (evMenu.type)
            {
            case Event::MouseButtonPressed:
            {
                switch (evMenu.key.code)
                {
                case Mouse::Left:

                    if (evMenu.mouseButton.x >= 530 && evMenu.mouseButton.x <= 750)
                    {
                        if (evMenu.mouseButton.y >= 335 && evMenu.mouseButton.y <= 392)
                        {
                            music.stop();
                            setup(window);
                        }

                        if (evMenu.mouseButton.y >= 459 && evMenu.mouseButton.y <= 516)
                        {
                            optionMenu(evMenu, texture, window);
                            if (audioToggle)
                            {
                                cout << "";
                            }
                            else {
                                music.stop();
                            }
                        }

                        if (evMenu.mouseButton.y >= 581 && evMenu.mouseButton.y <= 638)
                        {
                            window.close();
                        }
                    }
                }
            }
            }
        }

        window.draw(bgImageMenu);

        window.display();
    }
}

bool isAudioRunning(bool& audioToggle)
{
    return audioToggle;
}