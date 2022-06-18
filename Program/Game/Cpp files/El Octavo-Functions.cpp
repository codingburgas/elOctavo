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
    RectangleShape ground;

    Sound soundJump, soundWalk;
	SoundBuffer jumpBuffer, walkBuffer; 
}

using namespace variables;

void moveCharacter(int& keyTime, RenderWindow& window);
void moveCameraFirstStage(string direction, Sprite& image);
void moveCameraSecondStage(string direction, Sprite& image);
void moveCharacter(int& keyTime, RenderWindow& window);

void setVars()
{
    keyTime = 0;

    bgTexture.loadFromFile("../Images and fonts/Bg/test bg.png");

    bgImage.setTexture(bgTexture);

    //setting position of the background
    bgImage.setOrigin(1920, 1080);

    ground.setSize(Vector2f(1280, 150));
    ground.setPosition(Vector2f(0, 570));
    ground.setFillColor(Color::Black);

    plrT.loadFromFile("../Images and fonts/Main character/unknown.png");
    plrT.setRepeated(true);

    jumpBuffer.loadFromFile("../Audios/Jump.wav");
    walkBuffer.loadFromFile("../Audios/Walk.wav");

    soundJump.setBuffer(jumpBuffer);
    soundWalk.setBuffer(walkBuffer);

    soundJump.setVolume(15.0f);
    soundWalk.setVolume(35.0f);
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

        plr.updateMovement(deltaTime, soundWalk, soundJump);
        moveCharacter(keyTime, window);

        window.clear(Color::Green);

        window.draw(bgImage);
        window.draw(ground);
        plr.draw(window);

        //display character
        window.display();
    }
}

void moveCameraSecondStage(string direction, Sprite& image)
{

    //in first stage we have AD moving so we have two side moving
    if (direction == "left" && image.getPosition().x <= 1920)
    {
        image.move(200.0f * deltaTime, 0.f);
    }

    if (direction == "right" && image.getPosition().x >= -420)
    {
        image.move(-(200.0f * deltaTime), 0.f);
    }
}

void moveCameraFirstStage(string direction, Sprite& image) 
{    
    //in first stage we have WASD moving so we have four side moving
    if (direction == "up" && image.getPosition().y <= 1080)
    {
        image.move(0.f, 200.0f * deltaTime);
    }

    if (direction == "down" && image.getPosition().y >= -280)
    {
        image.move(0.f, -(200.0f * deltaTime));
    }

    moveCameraSecondStage(direction, image);
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
            moveCameraSecondStage("left", bgImage);
            keyTime = 0;
        }

        if (Keyboard::isKeyPressed(Keyboard::D))
        {
            moveCameraSecondStage("right", bgImage);
            keyTime = 0;
        }

        if (Keyboard::isKeyPressed(Keyboard::W))
        {
            moveCameraSecondStage("up", bgImage);
            keyTime = 0;
        }

        if (Keyboard::isKeyPressed(Keyboard::S))
        {
            moveCameraSecondStage("down", bgImage);
            keyTime = 0;
        }
    }
}

void characterHit(int& keyTime)
{
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

bool checkCollideWithGround(RectangleShape& body) {
    return ground.getGlobalBounds().intersects(body.getGlobalBounds());
}