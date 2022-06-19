#include "../Header files/Precompile.h"
#include "../Header files/El Octavo-Functions.h"
#include "../Header files/GameClass.h"
#include "../Header files/Additional Functions.h"

namespace variables {
    int keyTime = 0;
    float deltaTime = 0.0f;
    bool movementToggle = false;

    Event ev;

    Texture bgTexture;
    Sprite bgImage;
    Texture plrT;
    RectangleShape ground;

    Sound soundJump, soundWalk;
	SoundBuffer jumpBuffer, walkBuffer; 

    float fps;
    Clock c = Clock::Clock();
    Time previousTime = c.getElapsedTime();
    Time currentTime;

    Font font;
    Text fpsCounter;

    int roundedFps;
}

using namespace variables;

void moveCharacter(int& keyTime, RenderWindow& window);
void moveCameraFirstStage(string direction, Sprite& image);
void moveCameraSecondStage(string direction, Sprite& image);

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

    font.loadFromFile("../Images and fonts/Fonts/Header font.ttf");
    fpsCounter.setFont(font);
    fpsCounter.setCharacterSize(62);
}

void setup(RenderWindow& window)
{
    setVars();

    // start of sussy variables

    Clock clock;
    Player plr(&plrT, Vector2u(3, 2), 0.3f, 150.0f);
    bgImage.setPosition(window.getSize().x / 2, window.getSize().y / 2);

    // end of sussy variables
    window.setFramerateLimit(60);

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

        plr.updateMovement(deltaTime, soundWalk, soundJump, movementToggle);
        moveCharacter(keyTime, window);

        window.clear(Color::Green);

        window.draw(bgImage);
        
        if (movementToggle) {
            window.draw(ground);
        }

        plr.draw(window);
        
        // calculate fps
        currentTime = c.getElapsedTime();
        fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds());
        previousTime = currentTime;

        // show fps
        
        roundedFps = (int)fps;
        fpsCounter.setString(to_string(roundedFps));

        

        fpsCounter.setPosition(1200, 20);
        window.draw(fpsCounter);
        
        // display everything
        window.display();


    }
}

void moveCameraSecondStage(string direction, Sprite& image)
{
   //in second stage we have AD moving so we have two side moving
    if (direction == "up" && image.getPosition().y <= 1080)
    {
        image.move(0.f, 200.0f * deltaTime);
    }

    if (direction == "down" && image.getPosition().y >= -280)
    {
        image.move(0.f, -(200.0f * deltaTime));
    }
    
}

void moveCameraFirstStage(string direction, Sprite& image) 
{    
    //in first stage we have WASD moving so we have four side moving
    

    if (direction == "left" && image.getPosition().x <= 1920)
    {
        image.move(200.0f * deltaTime, 0.f);
    }

    if (direction == "right" && image.getPosition().x >= -420)
    {
        image.move(-(200.0f * deltaTime), 0.f);
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
            moveCameraFirstStage("left", bgImage);
            keyTime = 0;
        }

        if (Keyboard::isKeyPressed(Keyboard::D))
        {
            moveCameraFirstStage("right", bgImage);
            keyTime = 0;
        }

        if (Keyboard::isKeyPressed(Keyboard::W))
        {
            moveCameraFirstStage("up", bgImage);
            keyTime = 0;
        }

        if (Keyboard::isKeyPressed(Keyboard::S))
        {
            moveCameraFirstStage("down", bgImage);
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