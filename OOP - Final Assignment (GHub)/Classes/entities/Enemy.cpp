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
	frameSize = Rect(0.0F, 0.0F, 32.0F, 32.0F);
	view = Maze::SQUARE_SIZE * 2;

	switch (ghost)
	{
	case 1: // Blinky (Red)
		setName("Blinky");
		break;

	case 2: // Pinky (Pink)
		setName("Pinky");
		break;

	case 3: // Inky (Blue)
		setName("Inky");
		break;

	case 4: // Clyde (Orange)
	default:
		setName("Clyde");
		setTextureRect(frameSize);
		WaitTimeMax = 5.0F;
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
		setTexture("images/ghostB.png");
	}
	else
	{
		setOpacity(1.0F);
		setSpeed(1.0F); // makes the enemy slower

		// identifies based on the name of the ghost.
		if (ustd::equalsIgnoreCase(getName(), "Blinky"))
		{
			setTexture("images/ghostN.png");
		}
		else if (ustd::equalsIgnoreCase(getName(), "Pinky"))
		{
			setTexture("images/ghostN.png");
		}
		else if (ustd::equalsIgnoreCase(getName(), "Inky"))
		{
			setTexture("images/ghostN.png");
		}
		else if (ustd::equalsIgnoreCase(getName(), "Clyde"))
		{
			setTexture("images/ghostN.png");
		}
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
			waitTimer = 0.0F;
		return;
	}
	

	if (getDirection() == 0) // if the entity is currently not moving.
	{
		// mazePos = Vec2(curPos.x / Maze::SQUARE_SIZE, curPos.y / Maze::SQUARE_SIZE);
		setDirection(rand() % 4 + 1);

		

	}


	entity::Entity::update(deltaTime);
}
