#include "Precompile.h"
#include "El Octavo-Functions.h";
#include "GameClass.h";

namespace variables {
    int keyTime = 0;
    RenderWindow window(VideoMode(1500, 800), "The legend of Kurabirov", sf::Style::Titlebar | sf::Style::Close);;
    Event ev;
    Texture bgTexture;
    Sprite bgImage;
    Player plr;
    Texture plrT;
    Sprite plrS;
}

using namespace variables;

void update(int& keyTime, RectangleShape& square, RenderWindow& window);
void moveCamera(string direction, Sprite& image);

void setVars()
{
    keyTime = 0;

    window.setFramerateLimit(60);

    bgTexture.loadFromFile("../Images and fonts/Bg/test bg.png");
    bgImage.setTexture(bgTexture);

    plrT.loadFromFile("../Images and fonts/Main character/Main Character 81x129.png");
    plrS.setTexture(plrT);


    plr.setPublicVariables(window.getSize().x / 2, window.getSize().y / 2, 100, plrS);
    plr.setValues();

    //setting position of the background
    bgImage.setOrigin(1920, 1080);
    bgImage.setPosition(window.getSize().x / 2, window.getSize().y / 2);
}

void moveCamera(string direction, Sprite& image) {
    if (direction == "left" && image.getPosition().x != 1920) 
    {
        image.move(5.f, 0.f);
    }

    if (direction == "right" && image.getPosition().x != -420) 
    {
        image.move(-5.f, 0.f);
    }

    if (direction == "up") 
    {
        if (image.getPosition().y != 1080) {
            image.move(0.f, 5.f);
        }
        else {
            if (!plr.getMoved()) {
                plr.updatePos(0.f, 5.f);
                
                if (plr.getPos('y') >= ) {

                }
            }
        }
    }


    if (direction == "down" && image.getPosition().y != -280) 
    {
        image.move(0.f, -5.f);
    }
}

void update(int& keyTime, RectangleShape& square, RenderWindow& window)
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

        if (Mouse::isButtonPressed(Mouse::Left))
        {
            square.setFillColor(Color::Blue);
            keyTime = 0;
        }
        else {
            square.setFillColor(Color::Red);
            keyTime = 0;
        }
    }
}


void setup()
{
    setVars();

    while (window.isOpen())
    {
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

        window.clear(Color::Green);

        window.draw(bgImage);

        //display character
        plr.draw(window);

        window.display();
    }
}