#include "entities/Dot.h"

// CLASS FOR PAC DOTS
// the constructor for the pac-dot
entity::Dot::Dot() : Dot(entity::etag::pacdot) {}

// protected constructor, exclusively for the Pellet class.
entity::Dot::Dot(entity::etag tag) : entity::Entity(tag, "images/dot.png", 2.0F)
{
	frameSize = Rect(0.0F, 0.0F, 32.0F, 32.0F);
	setTextureRect(frameSize); // shares image file with power pellet

	setCollisionBody(new OOP::PrimitiveSquare(Vec2(32.0F / 2.0F, 32.0F / 2.0F), 32.0F)); // hitbox
	setPoints(10);
}

entity::Dot::~Dot()
{
}

void entity::Dot::update(float deltaTime)
{
}


// CLASS FOR POWER PELLETS
// constructor
entity::Pellet::Pellet() : Dot(etag::powerpellet)
{
	// frame size set in parent constructor
	setTextureRect(Rect(0.0F + frameSize.getMaxX(), 0.0F, frameSize.getMaxX(), frameSize.getMaxY())); // shares image file with pacdot
	setPoints(50);
}

entity::Pellet::~Pellet() {}

void entity::Pellet::update(float deltaTime)
{
	Dot::update(deltaTime);
}
