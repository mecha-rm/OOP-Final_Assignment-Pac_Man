#include "PMG_MenuScene.h"



PMG_MenuScene::PMG_MenuScene() : Scene(), mouse(OOP::MouseListener(this)), keyboard(OOP::KeyboardListener(this)) {}

Scene * PMG_MenuScene::createScene()
{
	return nullptr;
}

void PMG_MenuScene::onEnter() { Scene::onEnter(); }

void PMG_MenuScene::onExit() { Scene::onExit(); }

bool PMG_MenuScene::init()
{
	return false;
}

void PMG_MenuScene::initSprites()
{
}

void PMG_MenuScene::onMousePressed(EventMouse::MouseButton mouseButt, Event * event)
{
	EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event); //casting as a mouse event

}

void PMG_MenuScene::onMouseReleased(EventMouse::MouseButton mouseButt, Event * event)
{
	EventMouse* mouseEvent = dynamic_cast<EventMouse*>(event); //casting as a mouse event

}

void PMG_MenuScene::update(float deltaTime)
{
}

