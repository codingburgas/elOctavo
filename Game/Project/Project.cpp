#include "Project.h"

void update(int &keyTime, RectangleShape &square, RenderWindow& window);

void draw(RenderWindow &window, RectangleShape& square);

int main()
{ 
    int keyTime = 0;
   
    RenderWindow window(sf::VideoMode(1500, 800), "The legend of Kurabirov", sf::Style::Titlebar | sf::Style::Close);
    Event ev;

    window.setFramerateLimit(60);

    RectangleShape square(Vector2f(100.f, 100.f));
    square.setFillColor(Color::Red);

    //setting position of the characater
    square.setPosition(150, window.getSize().y / 2 + 150);

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

        draw(window, square);
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
            if (square.getPosition().x > 0)
            {
                square.move(-5.f, 0.f);
                keyTime = 0;
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::D))
        {
            if (square.getPosition().x + square.getSize().x < window.getSize().x)
            {
                square.move(5.f, 0.f);
                keyTime = 0;
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::W))
        {
            if (square.getPosition().y > 0)
            {
                square.move(0.f, -5.f);
                keyTime = 0;
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::S))
        {
            if (square.getPosition().y + square.getSize().y < window.getSize().y - 150)
            {
                square.move(0.f, 5.f);
                keyTime = 0;
            }
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

void draw(RenderWindow &window, RectangleShape& square)
{
    window.clear(Color::Green);

    //disdplay character
    window.draw(square);

    window.display();
}