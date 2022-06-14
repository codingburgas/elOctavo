#include "GameClasses.h"
#include "Precompile.h"

namespace variables {
    RectangleShape square(Vector2f(120, 50));
}

using namespace variables;

void Game::variables()
{
    this->window = nullptr;
    this->keyTime = 0;

    square.setFillColor(Color::Red);

    bgTexture.loadFromFile("../images/test.png");
    bgImage.setTexture(bgTexture);
}

void Game::windowInIt()
{
    this->videoMode.height = 1280;
    this->videoMode.width = 720;
    this->window = new RenderWindow(this->videoMode, "The legend of Kurabirov", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
}

const bool Game::running() const
{
    return this->window->isOpen();
}

Game::Game()
{
    this->variables();
    this->windowInIt();
}

Game::~Game()
{
    delete this->window;
}

void Game::update()
{
    while (this->window->isOpen())
    {
        while (this->window->pollEvent(this->ev))
        {
            if (this->ev->type == Event::Closed)
            {
                window->close();
            }

            if (this->ev->KeyPressed && this->ev->key.code == Keyboard::Escape)
            {
                window->close();
            }
        }
    }
}

void Game::render()
{

}

//we will put everything here
void setup()
{

}