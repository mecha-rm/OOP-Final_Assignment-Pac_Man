#pragma once

#include "KeyboardListener.h"
#include "audio/AudioLibrary.h"

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

	void initAudio(); // initializes the audio

	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event); // if a key is held down
	
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event); // if a key is let go
	
	// goes onto the next level
	void nextLevel();


	// collision between an entity and the other entities in the game.
	void collision(entity::Entity * ety, std::vector<entity::Entity *> & entities);

	void playerCollision();

	void update(float deltaTime); // the update loop

	CREATE_FUNC(PMG_GameplayScene);

private:

	// creates the maze and related values.
	void createMaze(int level);

	// turns on/off blue mode with 'bMode'
	void activeBlueMode(bool bMode);

	// removes an entity from the game
	void removeEntity(entity::Entity * ety, std::vector<entity::Entity *> & vector);

	Director * director;

	OOP::KeyboardListener keyboard;

	
	float timer = 0.0F; // the amount of time the game has been going for.

	// used to turn on/off 'blue mode'
	bool blueMode = false;
	float blueModeTimer = 0.0F; // counts down to the end of blue mode.
	const float BLUE_MODE_DURATION = 1.0F; // how long 'blue mode' lasts for.

	// the drawNode used to draw the maze. Move the draw node to move all of the assets on the maze.
	cocos2d::DrawNode * gamePane;
	DrawNode * infoPane; // the pane used to show information like the title and controls.

	cocos2d::Label * scoreLabel;
	Label * lifeLabel;
	
	const unsigned int SCORE_DIGITS = 10; // the amount of digits the score can have.
	int dots = 0; // the amount of pacdots in the game.


	Maze * maze; // the level information
	unsigned int level = 0; // the maze loaded up.
	const unsigned int TOTAL_LEVELS = 2; // the amount of levels in the game.

	entity::Player * plyr; // the player object
	
	// the game objects in the world.
	std::vector<entity::Entity *> gameObjects; 

	// the vector of enemies (ghosts).
	std::vector<entity::Enemy *> enemies;

protected:
} GameplayScene;

