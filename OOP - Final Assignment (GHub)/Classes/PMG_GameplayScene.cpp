#include "PMG_GameplayScene.h"

#include <iomanip>



PMG_GameplayScene::PMG_GameplayScene() : keyboard(OOP::KeyboardListener(this)) {}

Scene * PMG_GameplayScene::createScene() // making the scene
{
	Scene * scene = Scene::create();
	GameplayScene * layer = GameplayScene::create();
	
	scene->addChild(layer);
	return scene;
}

void PMG_GameplayScene::onEnter() { Scene::onEnter(); }

void PMG_GameplayScene::onExit() { Scene::onExit(); }

bool PMG_GameplayScene::init()
{
	if (!Scene::init()) // checks for proper initialization
		return false;

	director = Director::getInstance();
	this->scheduleUpdate(); // scheduled the update function
	
	// enabling the functionality of the keyboard.
	keyboard.setLabelVisible(false);
	keyboard.getListener()->onKeyPressed = CC_CALLBACK_2(GameplayScene::onKeyPressed, this);
	keyboard.getListener()->onKeyReleased = CC_CALLBACK_2(GameplayScene::onKeyReleased, this);
	keyboard.getListener()->setEnabled(true); // enables (or disables) keyboard

	initSprites();

	return true;
}

void PMG_GameplayScene::initSprites()
{
	gamePane = DrawNode::create();
	this->addChild(gamePane); // adds the gameplay section to the scene

	infoPane = DrawNode::create();
	// infoPane->setPositionX(500.0F);
	this->addChild(infoPane);


	scoreLabel = Label::create("00000000000", "fonts/Marker Felt.ttf", 40.0F);
	scoreLabel->setPosition(Vec2(1000.0F, 600.0F));
	infoPane->addChild(scoreLabel);

	// creating the area
	maze = new Maze(0); // creating the maze
	
	gameObjects = maze->generate(); // saves the game objects from the map.
	
	for (int i = 0; i < gameObjects.size(); i++)
	{
		if (gameObjects.at(i)->getCollisionBody() != nullptr)
			gameObjects.at(i)->getCollisionBody()->setVisible(entity::Entity::shapesVisible);

		if (gameObjects.at(i)->getTag() == entity::etag::enemy)
		{
			enemies.push_back((entity::Enemy * )gameObjects.at(i)); // downcasts and adds the enemy to an enemy specific vector
		}

		gamePane->addChild(gameObjects.at(i)->getSprite()); // gets the sprite, and adds it to the draw pane.
	}


	// creating the player.
	plyr = new entity::Player();
	plyr->getCollisionBody()->setVisible(entity::Entity::shapesVisible);
	plyr->setSpawnPosition(maze->getPlayerSpawn()); // gets the spawn point of the player in the maze.
	plyr->setPosition(maze->getPlayerSpawn()); 
	
	plyr->setPosition(500.0F, 500.0F); // comment out later
	gamePane->addChild(plyr->getSprite());


	entity::Entity::winSize = director->getWinSizeInPixels(); // saves the window size
}

// key has been pressed.
void PMG_GameplayScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event)
{
	EventKeyboard* keyboardEvent = dynamic_cast<EventKeyboard*>(event); // casting as a keyboard event

	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_UP_ARROW: // moving up
	case EventKeyboard::KeyCode::KEY_W:
		
		if(plyr->getDirection() != 1)
			plyr->setDirection(1);
		
		break;


	case EventKeyboard::KeyCode::KEY_DOWN_ARROW: // moving down
	case EventKeyboard::KeyCode::KEY_S:
		
		if (plyr->getDirection() != 2)
			plyr->setDirection(2);
		break;

	case EventKeyboard::KeyCode::KEY_LEFT_ARROW: // moving left
	case EventKeyboard::KeyCode::KEY_A:
		
		if (plyr->getDirection() != 3)
			plyr->setDirection(3);
		break;

	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW: // moving right
	case EventKeyboard::KeyCode::KEY_D:
		
		if (plyr->getDirection() != 4)
			plyr->setDirection(4);
		break;
	}

}

// key has been let go
void PMG_GameplayScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event)
{
	EventKeyboard* keyboardEvent = dynamic_cast<EventKeyboard*>(event); // casting as a keyboard event

	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_UP_ARROW: // moving up
	case EventKeyboard::KeyCode::KEY_W:
		// plyr->moveUp = false;

		break;

	case EventKeyboard::KeyCode::KEY_DOWN_ARROW: // moving down
	case EventKeyboard::KeyCode::KEY_S:
		// plyr->moveDown = false;
		break;

	case EventKeyboard::KeyCode::KEY_LEFT_ARROW: // moving left
	case EventKeyboard::KeyCode::KEY_A:
		// plyr->moveLeft = false;
		break;

	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW: // moving right
	case EventKeyboard::KeyCode::KEY_D:
		// plyr->moveRight = false;
		break;
	}

}

// collision between the player and the blocks
void PMG_GameplayScene::playerCollisions()
{
	// saves the proximity needed for the player to collide with the entity.
	Size proximity(Maze::SQUARE_SIZE * 2, Maze::SQUARE_SIZE * 2);

	for (int i = 0; i < gameObjects.size(); i++) // goes through all of the game objects
	{

		// if the entity is not within the check range, then they are skipped over.
		if (abs(gameObjects[i]->getPositionX() - plyr->getPositionX()) > proximity.width && abs(gameObjects[i]->getPositionY() - plyr->getPositionY()) > proximity.height)
			continue;

		if (OOP::Primitive::collision(plyr->getOffsetCollisionBody(), gameObjects.at(i)->getOffsetCollisionBody())) // checks collison betw=en the player and the collision body.
		{
			if (gameObjects[i]->getTag() == entity::etag::block) // if the player collided with a block.
			{
				// the player is shoved out of the wall in the direction they came from.
				// the vertical
				if (plyr->moveUp)
				{
					plyr->moveUp = false;
					plyr->setPosition(Vec2(plyr->getPositionX(), gameObjects[i]->getOffsetCollisionBody()->getPosition().y - gameObjects[i]->getCollisionBody()->m_HEIGHT));
				}
				if (plyr->moveDown)
				{
					plyr->moveDown = false;
					plyr->setPosition(Vec2(plyr->getPositionX(), gameObjects[i]->getOffsetCollisionBody()->getPosition().y + gameObjects[i]->getCollisionBody()->m_HEIGHT));
				}

				// the horizontal
				if (plyr->moveLeft)
				{
					plyr->moveLeft = false;
					plyr->setPosition(Vec2(gameObjects[i]->getOffsetCollisionBody()->getPosition().x + gameObjects[i]->getCollisionBody()->m_WIDTH, plyr->getPositionY()));
				}
				if (plyr->moveRight)
				{
					plyr->moveDown = false;
					plyr->setPosition(Vec2(gameObjects[i]->getOffsetCollisionBody()->getPosition().x - gameObjects[i]->getCollisionBody()->m_WIDTH, plyr->getPositionY()));
				}

				// plyr->setDirection(0);
			}
			else if (gameObjects[i]->getTag() == entity::etag::pacdot) // if it's a pac-dot, the player's score should increase.
			{
				plyr->addPoints(gameObjects[i]->getPoints());
				removeEntity(gameObjects[i], gameObjects);
			
			}
			else if (gameObjects[i]->getTag() == entity::etag::enemy) // the ghost
			{
				plyr->kill(); // makes the player lose a life.
			}
		}
	}
}

// collisions between the enemies and the tiles
void PMG_GameplayScene::enemyCollisions()
{
	Size proximity(Maze::SQUARE_SIZE * 2, Maze::SQUARE_SIZE * 2); // gets the proximity the object must be in for collision

	for each(entity::Enemy * ghost in enemies)
	{
		for (int i = 0; i < gameObjects.size(); i++)
		{
			if (ghost == gameObjects.at(i) || gameObjects.at(i)->getTag() == entity::enemy) // if the enemy has encountered another enemy
				continue;
			
			// if the entity is not within the check range, then they are skipped over.
			if (abs(gameObjects[i]->getPositionX() - ghost->getPositionX()) > proximity.width && abs(gameObjects[i]->getPositionY() - ghost->getPositionY()) > proximity.height)
				continue;
			

		}
	}
}

// removes an entity from the game
void PMG_GameplayScene::removeEntity(entity::Entity * ety, std::vector<entity::Entity *> & vector)
{
	ety->getSprite()->removeAllChildren(); // removes the children added to the sprite
	ety->getSprite()->removeFromParent(); // removes the sprite from its parent.
	
	// removes the entity from the vector.
	ustd::removeFromVector(vector, ety);
}


void PMG_GameplayScene::update(float deltaTime)
{
	std::string curScore = "";

	timer += deltaTime;

	plyr->update(deltaTime);

	entity::Enemy::playerPos = plyr->getPosition(); // informs the enemies of the player's position.

	for (entity::Entity * gObj : gameObjects) // updates the game objects
		gObj->update(deltaTime);

	curScore = std::to_string(plyr->getScore()); // setting the new score (as a string) 
	curScore = std::string(((signed)SCORE_DIGITS - curScore.length() > 0) ? (signed)SCORE_DIGITS - curScore.length() : 0, '0') + curScore;

	scoreLabel->setString(curScore);

	playerCollisions();
}

