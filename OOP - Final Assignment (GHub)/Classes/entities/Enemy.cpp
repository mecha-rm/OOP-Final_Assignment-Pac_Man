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
#include "entities/Enemy.h"
#include "Maze.h"

#include <random>

// the class for the enemies
// Maze * entity::Enemy::maze = nullptr;
Vec2 entity::Enemy::playerPos = Vec2(0.0F, 0.0F); // the position of the player.

// constructor
// ghost determines what enemy to make. [1] = Blinky (Red), [2] = Pinky (Pink), [3] = Inky (Blue), [4] = Clyde (Orange)
entity::Enemy::Enemy(unsigned short int ghost) : Entity(etag::enemy, "images/ghostN.png", 2.0F)
{
	OOP::SpriteSheetAnimation * tempAnime = nullptr;

	frameSize = Rect(0.0F, 0.0F, 32.0F, 32.0F);
	view = Maze::SQUARE_SIZE * 2;

	switch (ghost)
	{
	case 1: // Blinky (Red)
		setName("Blinky");
		setTexture("images/blinky.png");
		WaitTimeMax = 4.0F;
		break;

	case 2: // Pinky (Pink)
		setName("Pinky");
		setTexture("images/pinky.png");
		WaitTimeMax = 5.0F;
		break;

	case 3: // Inky (Blue)
		setName("Inky");
		setTexture("images/inky.png");
		WaitTimeMax = 6.0F;
		break;

	case 4: // Clyde (Orange)
	default:
		setName("Clyde");
		setTexture("images/clyde.png");
		WaitTimeMax = 7.0F;
		break;
	}

	setTextureRect(frameSize);
	setCollisionBody(new OOP::PrimitiveSquare(Vec2(frameSize.getMaxX() / 2.0F, frameSize.getMaxY() / 2.0F), 31.9F));
	setMagnitude(350.0F);
	waitTimer = WaitTimeMax;
	moveRight = true;


}

// destructor
entity::Enemy::~Enemy()
{
}

// makes the enemy stall for a predetermined amount of time.
void entity::Enemy::wait() { wait(WaitTimeMax); }

// makes the enemy stall for (x) amount of time
void entity::Enemy::wait(float time) { waitTimer = (time > 0.0F) ? time : 0.0F; }

// called to indiciate if blue mode is on or off.
void entity::Enemy::blueMode(bool bMode)
{
	if (bMode)
	{
		setSpeed(0.5F); // makes the enemy slower
		setTexture("images/blueghost.png");
		setTextureRect(frameSize);
	}
	else
	{
		setOpacity(1.0F);
		setSpeed(1.0F); // makes the enemy slower

		// identifies based on the name of the ghost.
		if (ustd::equalsIgnoreCase(getName(), "Blinky"))
		{
			setTexture("images/blinky.png");
		}
		else if (ustd::equalsIgnoreCase(getName(), "Pinky"))
		{
			setTexture("images/pinky.png");
		}
		else if (ustd::equalsIgnoreCase(getName(), "Inky"))
		{
			setTexture("images/inky.png");
		}
		else if (ustd::equalsIgnoreCase(getName(), "Clyde"))
		{
			setTexture("images/clyde.png");
		}

		setTextureRect(frameSize);
	}
}

// the update loop
void entity::Enemy::update(float deltaTime)
{
	Vec2 mazePos;
	Vec2 curPos = getPosition();
	
	if (waitTimer > 0.0F) //if the ghost shouldn't move yet.
	{
		waitTimer -= deltaTime;

		if (waitTimer < 0.0F)
		{
			waitTimer = 0.0F;
			if (inPen) // if they're in the pen, they're taken out of it.
			{
				setPositionY(getPositionY() + Maze::SQUARE_SIZE * 2.0F);
				inPen = false;
			}
		}
			
		return;
	}
	

	if (getDirection() == 0) // if the entity is currently not moving.
	{
		// mazePos = Vec2(curPos.x / Maze::SQUARE_SIZE, curPos.y / Maze::SQUARE_SIZE);
		setDirection(rand() % 4 + 1);


	}


	entity::Entity::update(deltaTime);
}
