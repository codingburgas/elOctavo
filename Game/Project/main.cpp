#include "Precompile.h"

void update(int &keyTime, RectangleShape &square, RenderWindow& window);
void moveCamera(string direction, Sprite &image);

Texture bgTexture;
Sprite bgImage;

int main()
{
    int keyTime = 0;

    RenderWindow window(sf::VideoMode(1500, 800), "The legend of Kurabirov", sf::Style::Titlebar | sf::Style::Close);
    Event ev;


    window.setFramerateLimit(60);

    bgTexture.loadFromFile("images/test.png");

    bgImage.setTexture(bgTexture);

    RectangleShape square(Vector2f(100.f, 100.f));
    square.setFillColor(Color::Red);

    //setting position of the characater
    square.setPosition(window.getSize().x / 2 - 50, window.getSize().y / 2 - 50);
    bgImage.setOrigin(1920, 1080);
    bgImage.setPosition(window.getSize().x / 2, window.getSize().y / 2);

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
        update(keyTime, square, window);

        window.clear(Color::Green);

        window.draw(bgImage);

        //display character
        window.draw(square);

        window.display();
    }
}

void moveCamera(string direction, Sprite &image) {
    if (direction == "left" && image.getPosition().x != 1920) {
        image.move(5.f, 0.f);
    }
    if (direction == "right" && image.getPosition().x != -420) {
        image.move(-5.f, 0.f);
    }
    if (direction == "up" && image.getPosition().y != 1080) {
        image.move(0.f, 5.f);
        cout << image.getPosition().y << endl;
    }
    if (direction == "down" && image.getPosition().y != -280) {
        image.move(0.f, -5.f);
        cout << image.getPosition().y << endl;
    }
}

void update(int& keyTime, RectangleShape &square, RenderWindow& window)
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
        }

        if (Keyboard::isKeyPressed(Keyboard::D))
        {
            moveCamera("right", bgImage);
        }

        if (Keyboard::isKeyPressed(Keyboard::W))
        {

            moveCamera("up", bgImage);
        }

        if (Keyboard::isKeyPressed(Keyboard::S))
        {
            moveCamera("down", bgImage);
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