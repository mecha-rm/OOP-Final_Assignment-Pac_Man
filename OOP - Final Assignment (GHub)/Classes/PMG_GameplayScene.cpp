#include "PMG_GameplayScene.h"



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

	return false;
}

void PMG_GameplayScene::initSprites()
{
}

void PMG_GameplayScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event)
{
	EventKeyboard* keyboardEvent = dynamic_cast<EventKeyboard*>(event); // casting as a keyboard event

}

void PMG_GameplayScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * event)
{
	EventKeyboard* keyboardEvent = dynamic_cast<EventKeyboard*>(event); // casting as a keyboard event

}

void PMG_GameplayScene::update(float deltaTime)
{
}
