#include "../Header files/Precompile.h"
#include "../Header files/El Octavo-Functions.h"
#include "../Header files/GameClass.h"

namespace variables {
    int keyTime = 0;
    float deltaTime = 0.0f;

    Event ev;

    Texture bgTexture;
    Sprite bgImage;
    Texture plrT;
}

using namespace variables;

void moveCharacter(int& keyTime, RenderWindow& window);
void moveCamera(string direction, Sprite& image);

void setVars()
{
    keyTime = 0;


    bgTexture.loadFromFile("../Images and fonts/Bg/test bg.png");

    bgImage.setTexture(bgTexture);

    //setting position of the background
    bgImage.setOrigin(1920, 1080);

    plrT.loadFromFile("../Images and fonts/Main character/unknown.png");
    plrT.setRepeated(true); 
}

void setup(RenderWindow& window)
{
    setVars();

    // start of sussy variables

    Clock clock;
    Player plr(&plrT, Vector2u(3, 2), 0.3f, 150.0f);
    window.setFramerateLimit(60);
    bgImage.setPosition(window.getSize().x / 2, window.getSize().y / 2);

    // end of sussy variables

    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();

        window.setKeyRepeatEnabled(true);

        while (window.pollEvent(ev))
        {
            if (ev.type == Event::Closed)
            {
                window.close();
            }

            if (ev.KeyPressed && ev.key.code == Keyboard::Escape)
            {
                window.close();
            }
        }

        plr.updateMovement(deltaTime);
        moveCharacter(keyTime, window);

        window.clear(Color::Green);

        window.draw(bgImage);
        plr.draw(window);

        //display character
        window.display();
    }
}

void moveCamera(string direction, Sprite& image) {
    //move camera of the window when character is moving
    if (direction == "left" && image.getPosition().x <= 1920) 
    {
        image.move(200.0f * deltaTime, 0.f);
    }

    if (direction == "right" && image.getPosition().x >= -420) 
    {
        image.move(-(200.0f * deltaTime), 0.f);
    }

    if (direction == "up" && image.getPosition().y <= 1080)
    {
        image.move(0.f, 200.0f * deltaTime);
    }

    if (direction == "down" && image.getPosition().y >= -280) 
    {
        image.move(0.f, -(200.0f * deltaTime));
    }
}

void moveCharacter(int& keyTime, RenderWindow& window)
{
    if (keyTime < 1)
    {
        keyTime++;
    }

    //WASD moving
    if (keyTime >= 1)
    {
        if (Keyboard::isKeyPressed(Keyboard::A))
        {
            moveCamera("left", bgImage);
            keyTime = 0;
        }

        if (Keyboard::isKeyPressed(Keyboard::D))
        {
            moveCamera("right", bgImage);
            keyTime = 0;
        }

        if (Keyboard::isKeyPressed(Keyboard::W))
        {
            moveCamera("up", bgImage);
            keyTime = 0;
        }

        if (Keyboard::isKeyPressed(Keyboard::S))
        {
            moveCamera("down", bgImage);
            keyTime = 0;
        }

        //Mouse events
        /*if (Mouse::isButtonPressed(Mouse::Left))
        {
            square.setFillColor(Color::Blue);
            keyTime = 0;
        }
        else {
            square.setFillColor(Color::Red);
            keyTime = 0;
        }*/
    }
}
