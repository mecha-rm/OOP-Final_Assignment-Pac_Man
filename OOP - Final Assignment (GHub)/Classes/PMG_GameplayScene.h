#pragma once

#include "KeyboardListener.h"

#include "Maze.h"
#include "entities/Entity.h"
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

	// collision between hte player and the blocks
	void playerCollisions();

	void update(float deltaTime); // the update loop

	CREATE_FUNC(PMG_GameplayScene);

private:
	Director * director;

	OOP::KeyboardListener keyboard;

	float timer = 0.0F; // the amount of time the game has been going for.
	
	// the drawNode used to draw the maze. Move the draw node to move all of the assets on the maze.
	cocos2d::DrawNode * gamePane;
	
	Maze * maze; // the level information
	entity::Player * plyr; // the player object
	
	// the game objects in the world.
	std::vector<entity::Entity *> gameObjects; 

	

protected:
} GameplayScene;

