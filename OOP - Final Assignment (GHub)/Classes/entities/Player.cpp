#include "entities/Player.h"

// creates pac-man
entity::Player::Player() : entity::Entity(etag::player, "images/pacman.png", 3.0F)
{
	setName("PAC-MAN");
	setDescription("The player, PAC-MAN.");
	frameSize = Rect(0.0F, 0.0F, 32.0F, 32.0F);
	setTextureRect(frameSize);

	setMagnitude(400.0F);

	// PAC-MAN's hitbox is slightly smaller than everyone else's so that we can seemlessly move through the cooridors
	setCollisionBody(new OOP::PrimitiveSquare(Vec2(32.0F / 2.0F, 32.0F / 2.0F), 31.9F));
}

entity::Player::~Player() {}

// the update loop for the player
void entity::Player::update(float deltaTime)
{
	

	entity::Entity::update(deltaTime);
}


