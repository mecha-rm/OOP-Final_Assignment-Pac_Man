#pragma once

#include "MouseListener.h"
#include "cocos2d.h"

using namespace cocos2d;

class PMG_MenuScene : public Scene
{
public:
	PMG_MenuScene();
	
	static Scene * createScene(); // creating the scene

	void onEnter(); // entering the scene

	void onExit(); // leaving the scene

	bool init(); // initializes scene

	void initSprites(); // initializes the sprites.

	void onMousePressed(EventMouse::MouseButton mouseButt, Event* event); //if a mouse button is pressed
	
	void onMouseReleased(EventMouse::MouseButton mouseButt, Event* event); //if a mouse button is released

	void update(float deltaTime); // the update loop

private:

	OOP::MouseListener mouse;

protected:
};

