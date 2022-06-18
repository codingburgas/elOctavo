#include "../Header files/GameClass.h";

namespace variables {
	Clock clock;
	Time currTime;
}

using namespace variables;

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
	body.setPosition(1280/2 + 47.5f, 720/2);
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

//update for moving character
void Player::updateMovement(float deltaTime)
{
	velocity.x = 0;

	if (jumpY == 0.0f) {
		jumpY = body.getPosition().y;
	}

	if (jumpY <= body.getPosition().y) {
		body.setPosition(body.getPosition().x, jumpY);
	}

	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		velocity.x -= speed * deltaTime;
	}

	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		velocity.x += speed * deltaTime;
	}

	if (Keyboard::isKeyPressed(Keyboard::Space)) {
		currTime = variables::clock.getElapsedTime();
		if (currTime.asSeconds() >= 1.0f) {
			variables::clock.restart();
			jumpY = body.getPosition().y;
			jump(deltaTime, 3.0);
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

	if (jumpY >= body.getPosition().y) {
		velocity.y += 160.0f * deltaTime;
	}
	else {
		velocity.y = 0;
	}
	body.move(0.0f, velocity.y);
}

void Player::draw(RenderWindow& window)
{
	window.draw(body);
}

void Player::jump(float deltaTime, float jumpHeight) {
	velocity.y = -sqrtf(2.0f * 160.0f * jumpHeight);
}