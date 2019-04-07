#include "entities/Player.h"

// creates pac-man
entity::Player::Player() : entity::Entity(etag::player, "images/pacman.png", 3.0F)
{
	setName("PAC-MAN");
	setDescription("The player, PAC-MAN.");
	frameSize = Rect(0.0F, 0.0F, 32.0F, 32.0F);
	setTextureRect(frameSize);

	setMagnitude(400.0F);
	setLives(LIVES_MAX);

	// PAC-MAN's hitbox is slightly smaller than everyone else's so that we can seemlessly move through the cooridors
	setCollisionBody(new OOP::PrimitiveSquare(Vec2(32.0F / 2.0F, 32.0F / 2.0F), 31.9F));
}

entity::Player::~Player() {}

// gets the player's score
unsigned int entity::Player::getScore() { return score; }

// sets the player's score
void entity::Player::setScore(unsigned int newScore) { score = newScore; }

// adds points to the player's score
void entity::Player::addPoints(unsigned int points) { score += points; }

// gets the number of lives the player has.
unsigned int entity::Player::getLives() { return lives; }

// sets hte amount of lives the player has.
void entity::Player::setLives(unsigned int lifeCount) { lives = lifeCount; }

void entity::Player::blueMode(bool bMode)
{
}

// has the player lose a life.
void entity::Player::kill()
{
	if (lives > 0) // if the player has livesl eft, they lose one.
	{
		lives--;
		setPosition(spawnPos);
	}
}

// the update loop for the player
void entity::Player::update(float deltaTime)
{

	


	entity::Entity::update(deltaTime);
}


