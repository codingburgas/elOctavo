#include "../Header files/GameClass.h";
#include "../Header files/El Octavo-Functions.h"
#include "../Header files/Menu.h"
#include "../Header files/Precompile.h"


namespace vars {
	Clock clock;
	Time currTime;
	bool jumped = false;
	int keyTime = 0;
}

using namespace vars;


//consturctors - setup variables
Player::Player(Texture* texture, Vector2u imageCount, float switchTime, float speed)
{
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	
	totalTime = 0.0f;

	currentImage.x = 0;

	uvRect.width = texture->getSize().x / float(imageCount.x);
	uvRect.height = texture->getSize().y / float(imageCount.y);

	//movement mechanic
	this->speed = speed;
	faceLeft = true;
	row = 0;

	body.setSize(Vector2f(81.0f, 129.0f));
	body.setOrigin(81.0f / 2, 129.0f / 2);
	body.setPosition(1280/2, 720/2);
	body.setTexture(texture);
}

//destructor
Player::~Player()
{
}

//update for displaying character
void Player::update(int row, float deltaTime, bool faceLeft)
{
	currentImage.y = row;
	totalTime += deltaTime;

	if(totalTime >= switchTime)
	{
		totalTime -= switchTime;
		currentImage.x++;

		if(currentImage.x >= imageCount.x)
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
}

void Player::moveCameraFirstStage(Sprite& image, float& deltaTime)
{
	image.move(-(250.0f * deltaTime), 0.f);
}

void Player::moveCharacter(int& keyTime, RenderWindow& window, Sprite& adventureBgImage, float& deltaTime)
{
	if (keyTime < 1)
	{
		keyTime++;
	}

	//WASD moving
	if (keyTime >= 1)
	{
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			moveCameraFirstStage(adventureBgImage, deltaTime);
			keyTime = 0;
		}
	}
}


//Update for moving character
void Player::updateMovement(float deltaTime, RenderWindow& window, Sprite adventureBgImage, Sound& soundWalk, Sound& soundJump, bool& toggle)
{

	velocity.x = 0;
	jumped = false;

	if (Keyboard::isKeyPressed(Keyboard::A)) {
		if (soundWalk.getStatus() == 0 && isAudioRunning(audioToggle) == true) {
			soundWalk.play();
		}

		velocity.x -= abs(speed - 25.0f) * deltaTime;
	}

	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		if (soundWalk.getStatus() == 0 && isAudioRunning(audioToggle) == true) {
			soundWalk.play();
		}

		velocity.x += abs(speed - 25.0f) * deltaTime;
	}

	if (!Keyboard::isKeyPressed(Keyboard::D) && !Keyboard::isKeyPressed(Keyboard::A) && !Keyboard::isKeyPressed(Keyboard::W) && !Keyboard::isKeyPressed(Keyboard::S)) {
		if (soundWalk.getStatus() == 2 && isAudioRunning(audioToggle) == true) {
			soundWalk.stop();
		}
	}
	

	if (toggle) {
		if (Keyboard::isKeyPressed(Keyboard::Space)) {

			currTime = vars::clock.getElapsedTime();
			if (currTime.asSeconds() >= 1.0f && !jumped && isAudioRunning(audioToggle) == true) {
				soundJump.play();
				vars::clock.restart();
				jumpY = body.getPosition().y;
				jump(deltaTime, 3.0);
				jumped = true;
			}
		}

		if (body.getPosition().x == 620.0f)
		{
			Player::moveCharacter(keyTime, window, adventureBgImage, deltaTime);
		}
	}
	else {
		velocity.y = 0;
		if (Keyboard::isKeyPressed(Keyboard::W))
		{
			if (soundWalk.getStatus() == 0 && isAudioRunning(audioToggle) == true) {
				soundWalk.play();
			}

			velocity.y -= abs(speed - 35.0f) * deltaTime;
		}

		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			if (soundWalk.getStatus() == 0 && isAudioRunning(audioToggle) == true) {
				soundWalk.play();
			}

			velocity.y += abs(speed - 35.0f) * deltaTime;
		}
	}
		

	if (velocity.x == 0.0f)
	{
		row = 0;
	}
	else
	{
		row = 1;
		if (velocity.x > 0.0f)
		{
			faceLeft = true;
		}

		else
		{
			faceLeft = false;
		}
	}

	update(row, deltaTime, faceLeft);
	body.setTextureRect(uvRect);

	if (toggle) {
		if (checkCollideWithGround(body)) {
			body.setPosition(body.getPosition().x, 495.0f);
		}

		if (checkCollideWithGround(body) && !jumped) {
			velocity.y = 0;
		}
		else {
			velocity.y += 160.0f * deltaTime;
		}
		body.move(velocity.x, velocity.y);
	}
	else {
		if (checkCollideWithHypotenuse(body)) {
			velocity.y = -velocity.x;
		}
		else if (checkCollideWithRamp(body))
		{
			body.setPosition(body.getPosition().x, 520.0f);
		}
		body.move(velocity.x, velocity.y);	
	}
}

void Player::draw(RenderWindow& window)
{
	window.draw(body);
}

void Player::jump(float deltaTime, float jumpHeight) {
	velocity.y = -sqrtf(2.0f * 160.0f * jumpHeight);
}

