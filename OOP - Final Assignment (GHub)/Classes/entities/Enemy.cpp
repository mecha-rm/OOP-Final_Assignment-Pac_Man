#include "entities/Enemy.h"
#include "Maze.h"

// the class for the enemies

Vec2 entity::Enemy::playerPos = Vec2(0.0F, 0.0F); // the position of the player.

// constructor
// ghost determines what enemy to make. [1] = Blinky (Red), [2] = Pinky (Pink), [3] = Inky (Blue), [4] = Clyde (Orange)
entity::Enemy::Enemy(unsigned short int ghost) : Entity(etag::enemy, "images/ghosts.png", 2.0F)
{
	frameSize = Rect(0.0F, 0.0F, 32.0F, 32.0F);
	view = Maze::SQUARE_SIZE * 2;

	switch (ghost)
	{
	case 1: // Blinky (Red)
		break;

	case 2: // Pinky (Pink)
		break;

	case 3: // Inky (Blue)
		break;

	case 4: // Clyde (Orange)
	default:
		setTextureRect(frameSize);
		break;
	}

	setCollisionBody(new OOP::PrimitiveSquare(Vec2(frameSize.getMaxX() / 2.0F, frameSize.getMaxY() / 2.0F), 32.0F));
	setMagnitude(350.0F);
	moveRight = true;


}

// destructor
entity::Enemy::~Enemy()
{
}

// the update loop
void entity::Enemy::update(float deltaTime)
{
	entity::Entity::update(deltaTime);
}
