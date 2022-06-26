#include "../Header files/Precompile.h"
#include "../Header files/El Octavo-Functions.h"
#include "../Header files/GameClass.h"
#include "../Header files/Additional Functions.h"
#include "../Header files/Menu.h"

// Npc class
Npc::Npc(Texture * texture, Vector2u imageCount, float switchTime, float speed, string name) {
    this->imageCount = imageCount;
    this->switchTime = switchTime;
    this->speed = speed;
    this->totalTime = 0.0f;
    this->currentImage.x = 0;
    this->name = name;
    this->posIndex = 0;
    this->reset = false;
    this->delay = false;
    this->plrFound = false;

    this->uvRect.width = texture->getSize().x / float(imageCount.x);
    this->uvRect.height = texture->getSize().y / float(imageCount.y);

    //movement mechanic
    this->faceLeft = true;
    this->row = 0;


    this->body.setSize(Vector2f(81.0f, 90.0f));
    this->body.setOrigin(81.0f / 2, 90.0f / 2);
    this->body.setPosition(1849.0f, 538.0f - 90.0f / 2);
    this->body.setTexture(texture);
}

Npc::~Npc() {
}

void Npc::draw(RenderWindow& window) {
    window.draw(this->body);
}

void Npc::moveX(float amount) {
    this->body.move(amount, 0.0f);
}

void Npc::update(int row, float deltaTime, bool delay) {
    currentImage.y = row;
    totalTime += deltaTime;

    if (totalTime >= switchTime)
    {
        totalTime -= switchTime;
        currentImage.x++;

        if (currentImage.x >= imageCount.x)
        {
            currentImage.x = 0;
        }
    }

    uvRect.top = currentImage.y * uvRect.height;

    if (faceLeft)
    {
        uvRect.left = (currentImage.x + 1) * abs(uvRect.width);
        uvRect.width = -abs(uvRect.width);
    }
    else
    {
        uvRect.left = currentImage.x * uvRect.width;
        uvRect.width = abs(uvRect.width);
    }

    body.setTextureRect(uvRect);
}

void Npc::moveTo(float pos[], float deltaTime, bool& done, bool& faceLeft, RectangleShape& plrBody, bool jumped, Sprite& adventureBgImage) {
    
    if (abs(body.getPosition().x - plrBody.getPosition().x) < 300 && abs(plrBody.getPosition().y - body.getPosition().y) < 80.0f && !jumped) {
        plrFound = true;
    }
    else {
        plrFound = false;
    }

    if (plrFound) {
        if (plrBody.getPosition().x > body.getPosition().x) {
            distance = plrBody.getPosition().x - body.getPosition().x;
            if (distance > 40.5f) {
                moveX(speed * deltaTime);
            }
            faceLeft = false;
        }
        else {
            distance = body.getPosition().x - plrBody.getPosition().x;
            if (distance > 40.5f) {
                moveX(-speed * deltaTime);
            }
            faceLeft = true;
        }
    }
    else if (!delay) {
        if (pos[posIndex] > body.getPosition().x) {
            distance = pos[posIndex] - body.getPosition().x;
            moveX(speed * deltaTime);
        }
        else {
            distance = body.getPosition().x - pos[posIndex];
            moveX(-speed * deltaTime);
        }
    }

    if (!plrFound) {
        if (distance <= 20) {
            if (!reset) {
                npcClock.restart();
                reset = true;
                //cout << "Reset" << endl;
                delay = true;

                if (faceLeft) 
                {
                    //cout << "if" << endl;
                    faceLeft = false;
                }
                else {
                    //cout << "else" << endl;
                    faceLeft = true;
                }
            
            }
        
            npcCurrentTime = npcClock.getElapsedTime();

            if (npcCurrentTime.asSeconds() >= 0.3) {
                posIndex++;
                if (posIndex > 1) {
                    posIndex = 0;
                }
                reset = false;
                delay = false;
            }
        }
    }
    else {
        if (distance <= 40.5f && abs(plrBody.getPosition().y - body.getPosition().y) < 64.5) {
            respawnPlayer(plrBody, body, adventureBgImage);
        }
    }
}

// CollisionBlock class
CollisionBlock::CollisionBlock(Vector2f pos, Vector2f size) {
    hitbox.setSize(size);
    hitbox.setPosition(pos);
}

CollisionBlock::~CollisionBlock() {
}

bool CollisionBlock::checkForCollision(RectangleShape& body) {
    if (body.getGlobalBounds().intersects(hitbox.getGlobalBounds())) {
        return true;
    }
    else {
        return false;
    }
}

void CollisionBlock::drawHitbox(RenderWindow& window) {
    window.draw(hitbox);
}

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

    //background for stage 2
    Texture messageTexture;
    Sprite messageImage;

    // player / npc
    Texture plrT;
    Texture npcT;
   
    //ground
    RectangleShape ground;
    //ramp
    Texture rampT;
    Sprite ramp;
    RectangleShape points[12];
    Vector2f pointsCopy[12];


    //sound
    Sound soundJump, soundWalk;
    SoundBuffer jumpBuffer, walkBuffer;

    //time
    Clock fpsClock = Clock::Clock();
    Time fpsPreviousTime = fpsClock.getElapsedTime();
    Time fpsCurrentTime;
    Clock npcClock = Clock::Clock();
    Time npcPreviousTime = npcClock.getElapsedTime();
    Time npcCurrentTime;

    //font
    Font font;

    //fps
    float fps;
    Text fpsCounter;
    int roundedFps;

    string cutsceneStr = "Press Q to talk with the mafia.";
    Text cutsceneText;

    bool drawBubble;

    CollisionBlock blocks[8] = { {Vector2f(2882, 490), Vector2f(117, 34)}, {Vector2f(1428, 338), Vector2f(211, 43)}, {Vector2f(3074, 443), Vector2f(181, 34)}, {Vector2f(3323, 395), Vector2f(181, 34)}, {Vector2f(4071, 441), Vector2f(109, 34)}, {Vector2f(5435, 461), Vector2f(117, 34)}, {Vector2f(5667, 380), Vector2f(171, 34)}, {Vector2f(5938, 305), Vector2f(474, 34)} };
    
    Vector2f blocksCopy[8] = {Vector2f(2428, 416), Vector2f(1428, 338), Vector2f(3074, 443), Vector2f(3323, 395), Vector2f(4071, 441), Vector2f(5435, 461), Vector2f(5667, 380), Vector2f(5938, 305)};

    bool done;

    float moved;

    Texture kurabirovTexture, mafiaTexture, nestashevTexture;
    Sprite kurabirovCutscene, mafiaCutscene, nestashevCutscene;

    string dialogScript = "Hello, you must be the boss's people!";
    Text textDialogScript;

    Clock timer;

    unsigned int character = 0;

    unsigned int dialogTurn = 0;

    bool enterDialogue = false;

    bool enterPressed = false;

    bool dialogueOver = false;

    bool imageTurn = true;
};


using namespace variables;

void moveStaticImages(RectangleShape& body, RenderWindow& window, Npc& test);

Vector2f getRampPos();
void respawnPlayer(RectangleShape& body);

void setVars()
{
    bgTexture.loadFromFile("../Images and fonts/Bg/test bg.png");
    bgImage.setTexture(bgTexture);
    drawBubble = false;

    adventureBgTexture.loadFromFile("../Images and fonts/Bg/GameMap.png");
    adventureBgImage.setTexture(adventureBgTexture);

    messageTexture.loadFromFile("../Images and fonts/Bg/message.png");
    messageImage.setTexture(messageTexture);

    messageImage.setPosition(500, 300);

    //setting position of the background
    bgImage.setOrigin(1920, 1080);

    ground.setSize(Vector2f(1280, 225));
    ground.setPosition(Vector2f(0, 535));
    ground.setFillColor(Color::Black);

    plrT.loadFromFile("../Images and fonts/Main character/unknown.png");
    plrT.setRepeated(true);

    npcT.loadFromFile("../Images and fonts/NPCs/enemy npc sprite sheet.png");
    npcT.setRepeated(true);

    rampT.loadFromFile("../Images and fonts/Ramp Test.png");
    ramp.setTexture(rampT);
    ramp.setOrigin(0, 0);
    ramp.setPosition(800, 430);

    jumpBuffer.loadFromFile("../Audios/Jump.wav");
    walkBuffer.loadFromFile("../Audios/Walk.wav");

    soundJump.setBuffer(jumpBuffer);
    soundWalk.setBuffer(walkBuffer);

    soundJump.setVolume(5.0f);
    soundWalk.setVolume(25.0f);

    font.loadFromFile("../Images and fonts/Fonts/Header font.ttf");
    fpsCounter.setFont(font);
    fpsCounter.setCharacterSize(56);

    cutsceneText.setPosition(20, 20);
    cutsceneText.setCharacterSize(30);
    cutsceneText.setFont(font);

    for (int i = 0; i < 12; i++) {
        points[i] = RectangleShape(Vector2f(10, 10));
        points[i].setOrigin(5, 5);
    }

    for (int i = 0; i < 12; i++) {
        if (i == 0) {
            points[i].setPosition(ramp.getPosition().x, ramp.getPosition().y + 110);
        }
        else {
            points[i].setPosition(points[i - 1].getPosition().x + 10, points[i - 1].getPosition().y - 10);
        }
    }

    for (int i = 0; i < 12; i++) {
        pointsCopy[i] = points[i].getPosition();
    }

    //cutscene setup
    kurabirovTexture.loadFromFile("../Images and fonts/Dialogues/KurabirovDialogue.png");
    mafiaTexture.loadFromFile("../Images and fonts/Dialogues/MobsterDialogue.png");
    nestashevTexture.loadFromFile("../Images and fonts/Dialogues/MobsterDialogue.png");

    kurabirovCutscene.setTexture(kurabirovTexture); 
    mafiaCutscene.setTexture(mafiaTexture);
    nestashevCutscene.setTexture(nestashevTexture);

    textDialogScript.setFont(font);
    textDialogScript.setFillColor(Color(0, 0, 0));
    textDialogScript.setPosition(100, 540);
    textDialogScript.setCharacterSize(50);
}

void setup(RenderWindow& window)
{
    setVars();

    int blocksSize = sizeof(blocks) / sizeof(*blocks);

    // start of sussy variables

    Clock clock;
    Player plr(&plrT, Vector2u(3, 2), 0.3f, 225.0f);
    Npc test(&npcT, Vector2u(3,1), 0.3f, 170.0f, "Test");
    //bgImage.setPosition(window.getSize().x / 2, window.getSize().y / 2);


    // end of sussy variables

    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        float moveToPos[2] = {blocks[1].hitbox.getPosition().x + 200, blocks[0].hitbox.getPosition().x - 200};
        deltaTime = clock.restart().asSeconds();

        window.setKeyRepeatEnabled(true);


        while (window.pollEvent(ev))
        {
            if (ev.type == Event::Closed)
            {
                window.close();
            }

            if (ev.type == Event::KeyPressed && ev.key.code == Keyboard::Escape)
            {
                window.close();
            }

            if (ev.type == Event::KeyReleased && ev.key.code == Keyboard::Enter) {
                enterPressed = false;
            }

        }

        if (plr.body.getPosition().x >= messageImage.getPosition().x - 200.0f && plr.body.getPosition().x <= messageImage.getPosition().x + 200.0f)
        {
            cutsceneText.setString(cutsceneStr);
            if (!dialogueOver) {
                drawBubble = true;
            }

            if (Keyboard::isKeyPressed(Keyboard::Q))
            {
                enterDialogue = true;
            }
                    
        }
        else {
            cutsceneText.setString("");
            drawBubble = false;
        }

        if (enterDialogue) {
            //cout << "ent" << endl;


            if (Keyboard::isKeyPressed(Keyboard::Enter) && !enterPressed)
            {
                dialogTurn++; 
                
                cout << dialogTurn << endl;
                enterPressed = true;
                character = 0;

            }

            if (dialogTurn == 1)
            {
                dialogScript = "Yes we are. Anyway, your task is to\nfind Nestashev and get netractor certificate.";
                imageTurn = false;
            }

            if (dialogTurn == 2)
            {
                dialogScript = "Certificate for netractors? Are you OK!";
                imageTurn = true;
            }
           
            if (dialogTurn == 3)
            {
                dialogScript = "Yes this is the order.\nNow go this way and you will reach nestashev.";
                imageTurn = false;
            }

            if (dialogTurn == 4)
            {
                dialogScript = "All right, I'll go. See you later.\nI have to beat nestashev for money!";
                imageTurn = true;
            }

            if (dialogTurn == 5)
            {
                textDialogScript.setString("");
                enterDialogue = false;
                dialogueOver = true;
                imageTurn = true;
            }

            if (enterDialogue) {
                if (timer.getElapsedTime().asSeconds() > 0.01 && character < dialogScript.length())
                {
                    timer.restart();

                    character++;

                    textDialogScript.setString(string(dialogScript.substr(0, character)));
                }
            }
            
        }

        if (dialogueOver)
        {
            cutsceneText.setString("");
            drawBubble = false;
        }
        

        plr.updateMovement(deltaTime, window, adventureBgImage, soundWalk, soundJump, movementToggle, blocks, blocksSize);
        test.update(0, deltaTime,test.delay);

        window.clear(Color::Green);

        if (movementToggle) {
            window.draw(ground);
        }

        window.draw(adventureBgImage);
        window.draw(ramp);

        /*for (int i = 0; i < 8; i++) {
            window.draw(blocks[i].hitbox);
        }*/

        window.draw(test.body);

        plr.draw(window);

        test.moveTo(moveToPos, deltaTime, done, test.faceLeft, plr.body, plr.jumped, adventureBgImage);

        // calculate fps
        fpsCurrentTime = fpsClock.getElapsedTime();
        fps = 1.0f / (fpsCurrentTime.asSeconds() - fpsPreviousTime.asSeconds());
        fpsPreviousTime = fpsCurrentTime;

        // show fps
        roundedFps = (int)fps;
        fpsCounter.setString(to_string(roundedFps));
        fpsCounter.setPosition(1200, 20);

        if (isShowingFPS(showFPS) == true)
        {
            window.draw(fpsCounter);
        }
        
        window.draw(cutsceneText);

        /*for (int i = 0; i < 11; i++) {
            window.draw(points[i]);
        }*/

        // draw message bubble
        if (drawBubble) {
            window.draw(messageImage);
        }

        moveStaticImages(plr.body, window, test);

        if (enterDialogue)
        {
            if (imageTurn)
            {
                window.draw(kurabirovCutscene);
            }
            else {
                window.draw(mafiaCutscene);
            }
        }

        window.draw(textDialogScript);

        window.display();
    }
}

bool checkCollideWithGround(RectangleShape& body) {
    return ground.getGlobalBounds().intersects(body.getGlobalBounds());
}

bool checkCollideWithRamp(RectangleShape& body) {
    /*if (ramp.getGlobalBounds().intersects(body.getGlobalBounds())) {
        Image rampImage = rampT.copyToImage();

        int pixelX = body.getPosition().x - ramp.getPosition().x;
        int pixelY = (body.getPosition().y + 44) - ramp.getPosition().y;

        if ((pixelX < 110 && pixelX > 0) && (pixelY < 110 && pixelY >= 0)) {
            if (rampImage.getPixel(pixelX, pixelY).a != 0) {
                return true;
            }
            else {
                return false;
            }
        }
    }*/

    for (int i = 0; i < 12; i++) {
        if (points[i].getGlobalBounds().intersects(body.getGlobalBounds()) && body.getPosition().x <= ramp.getPosition().x + 110) {
            return true;
        }
    }

    return false;
}

Vector2f getRampPos() {
    return ramp.getPosition();
}

void moveStaticImages(RectangleShape& body, RenderWindow& window, Npc& test)
{
    if (Keyboard::isKeyPressed(Keyboard::D))
    {
        if (body.getPosition().x >= window.getSize().x / 2)
        {
            //make images static
            messageImage.move(-(225.0f * deltaTime), 0.f);
            ramp.move(-(225.0f * deltaTime), 0.f);
            test.moveX(-(225.0f * deltaTime));

            for (int i = 0; i < 8; i++) {
                blocks[i].hitbox.move(-(225.0f * deltaTime), 0.f);
            }

            for (int i = 0; i < 11; i++) {
                points[i].move(-(225.0f * deltaTime), 0.f);
            }

            if (moved < 1100.19) {
                moved += 225.0f * deltaTime;
            }
        }
    }
}

void resetStaticImages(float& offset, RectangleShape& npcBody, Sprite& adventureBgImage) {
    cout << offset << endl;
    
    messageImage.setPosition(500 - 1101, 300);
    ramp.setPosition(800 - 1101, 430);
    npcBody.setPosition(1849.0f - 1101, 538.0f - 90.0f / 2);

    for (int i = 0; i < 8; i++) {
        blocks[i].hitbox.setPosition(blocksCopy[i].x - 1101, blocksCopy[i].y);
    }

    for (int i = 0; i < 11; i++) {
        points[i].setPosition(pointsCopy[i].x - 1101, pointsCopy[i].y);
    }

    adventureBgImage.setPosition(0.f - 1101, 0.f);
}

void cutscene(RectangleShape& body, string& cutsceneStr, Sprite& adventureBgImage, Sprite& messageImage, RenderWindow& window)
{
    if (body.getPosition().x >= messageImage.getPosition().x - 200.0f && body.getPosition().x <= messageImage.getPosition().x + 200.0f)
    {
        cutsceneText.setString(cutsceneStr);
        drawBubble = true;
    }
    else {
        cutsceneText.setString("");
        drawBubble = false;
    }
}

void respawnPlayer(RectangleShape& body, RectangleShape& npcBody, Sprite& adventureBgImage) {
    body.setPosition(150, 720 / 2);
    resetStaticImages(moved, npcBody, adventureBgImage);
}
