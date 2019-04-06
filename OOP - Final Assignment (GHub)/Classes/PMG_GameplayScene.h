#pragma once

#include "KeyboardListener.h"

#include "Maze.h"
#include "entities/Player.h"

#include "cocos2d.h"

using namespace cocos2d;

typedef class PMG_GameplayScene : public Scene
{
public:
	PMG_GameplayScene();
	
	static Scene * createScene(); // creating the scene
	
	void onEnter(); // entering the scene

	void onExit(); // leaving the scene

	bool init(); // initializes scene

	void initSprites(); // initializes the sprites.

	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event); // if a key is held down
	
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event); // if a key is let go


	// void collisions();

	// collision between the player and the blocks
	void playerCollisions();
	// collisions between enemies and tiles
	void enemyCollisions();

	void update(float deltaTime); // the update loop

	CREATE_FUNC(PMG_GameplayScene);

private:

	// removes an entity from the game
	void removeEntity(entity::Entity * ety, std::vector<entity::Entity *> & vector);

	Director * director;

	OOP::KeyboardListener keyboard;

	float timer = 0.0F; // the amount of time the game has been going for.
	
	// the drawNode used to draw the maze. Move the draw node to move all of the assets on the maze.
	cocos2d::DrawNode * gamePane;
	DrawNode * infoPane; // the pane used to show information like the title and controls.

	cocos2d::Label * scoreLabel;
	
	const unsigned int SCORE_DIGITS = 10; // the amount of digits the score can have.


	Maze * maze; // the level information
	entity::Player * plyr; // the player object
	
	// the game objects in the world.
	std::vector<entity::Entity *> gameObjects; 

	// the vector of enemies.
	std::vector<entity::Enemy *> enemies;

	

protected:
} GameplayScene;

