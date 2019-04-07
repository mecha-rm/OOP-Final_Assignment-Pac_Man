/*
* Project: Object Oriented Programming - Final Project - PAC-MAN
* Date: 04/06/2019

* Group Members: Assignment Group 6
	- Caleb Birnie (100699828)
	- Nathan Tuck (100708651)
	- Roderick “R.J.” Montague (100701758)
	- Ryan Burton (100707511)
	- Tavis East (100702011)

*/
#include "Block.h"

// constructor
entity::Block::Block(Vec2 pos) : entity::Entity(entity::etag::block, "images/block.png", 1.0F)
{
	frameSize = Rect(0.0F, 0.0F, 32.0F, 32.0F);
	setTextureRect(frameSize);

	setPosition(pos);

	setCollisionBody(new OOP::PrimitiveSquare(Vec2(32.0F / 2.0F, 32.0F / 2.0F), 32.0F));
}

// constructor 2
entity::Block::Block(float x, float y) : Block(Vec2(x, y)) {}

entity::Block::~Block() {}

// update loop
void entity::Block::update(float deltaTime)
{
}
