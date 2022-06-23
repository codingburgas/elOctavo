#include "../Header files/Precompile.h"
#include "../Header files/El Octavo-Functions.h"
#include "../Header files/GameClass.h"
#include "../Header files/Additional Functions.h"

namespace variables {

    //movemenent
    float deltaTime = 0.0f;
    bool movementToggle = true;

    //event
    Event ev;

    //background
    Texture bgTexture;
    Sprite bgImage;

    //background for stage 2
    Texture adventureBgTexture;
    Sprite adventureBgImage;

    //ground
    Texture plrT;
    RectangleShape ground;

    //ramp
    Texture rampT;
    Sprite ramp;

    //sound
    Sound soundJump, soundWalk;
    SoundBuffer jumpBuffer, walkBuffer;

    //time
    Clock c = Clock::Clock();
    Time previousTime = c.getElapsedTime();
    Time currentTime;

    //font
    Font font;

    //fps
    float fps;
    Text fpsCounter;
    int roundedFps;
}

using namespace variables;

void setVars()
{
    bgTexture.loadFromFile("../Images and fonts/Bg/test bg.png");
    bgImage.setTexture(bgTexture);

    adventureBgTexture.loadFromFile("../Images and fonts/Bg/Part1 map.png");
    adventureBgImage.setTexture(adventureBgTexture);

    //setting position of the background
    bgImage.setOrigin(1920, 1080);

    ground.setSize(Vector2f(1280, 225));
    ground.setPosition(Vector2f(0, 535));
    ground.setFillColor(Color::Black);

    plrT.loadFromFile("../Images and fonts/Main character/unknown.png");
    plrT.setRepeated(true);

    rampT.loadFromFile("../Images and fonts/Ramp Test.png");
    ramp.setTexture(rampT);

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
    Player plr(&plrT, Vector2u(3, 2), 0.3f, 225.0f);
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

        plr.updateMovement(deltaTime, window, adventureBgImage,soundWalk, soundJump, movementToggle);

        window.clear(Color::Green);

        if (movementToggle) {
            window.draw(ground);
        }

        window.draw(adventureBgImage);

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

        window.display();
    }
}

bool checkCollideWithGround(RectangleShape& body) {
    return ground.getGlobalBounds().intersects(body.getGlobalBounds());
}

bool checkCollideWithRamp(RectangleShape& body) {
    return ramp.getGlobalBounds().intersects(body.getGlobalBounds());
}