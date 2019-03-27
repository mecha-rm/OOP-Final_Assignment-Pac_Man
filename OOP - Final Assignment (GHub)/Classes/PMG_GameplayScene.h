#pragma once

#include "KeyboardListener.h"

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

	void update(float deltaTime); // the update loop

	CREATE_FUNC(PMG_GameplayScene);

private:
	Director * director;

	OOP::KeyboardListener keyboard;

protected:
} GameplayScene;

