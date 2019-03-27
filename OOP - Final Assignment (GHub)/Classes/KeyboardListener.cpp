#include "KeyboardListener.h"



OOP::KeyboardListener::KeyboardListener(cocos2d::Scene * scene) : keyboardListener(cocos2d::EventListenerKeyboard::create())
{
	// std::bind(&OOP::MouseListener::OnMouseMove, this, std::placeholders::_1); // creates the callback
	keyboardListener->onKeyPressed = CC_CALLBACK_2(OOP::KeyboardListener::onKeyPressed, this); // creating key pressed callback
	keyboardListener->onKeyReleased = CC_CALLBACK_2(OOP::KeyboardListener::onKeyReleased, this); // creacting key released callback

	keyboardLabel = cocos2d::Label::create("Hello", "fonts/arial.ttf", 30); // creates the label
	keyboardLabel->setGlobalZOrder(10.2F); // the mouse label should be in front of everything.
	keyboardLabel->setPosition(cocos2d::Vec2(650.0F, 500.0F)); // repositioning the label
	keyboardLabel->setVisible(false); // making tjhe label not visible

	this->scene = scene;
	this->scene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this->scene); // adds the keyboard listener to the event dispatcher
	this->scene->addChild(keyboardLabel); // adds the keyboard label to the scene.
}


OOP::KeyboardListener::~KeyboardListener() { 
	scene->getEventDispatcher()->removeEventListener(keyboardListener);
	/*keyboardListener->release();*/ }

// key down
void OOP::KeyboardListener::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	cocos2d::EventKeyboard* keyboardEvent = dynamic_cast<cocos2d::EventKeyboard*>(event); // casting as a keyboard event
	
	/*
	switch (keyCode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
		break;

	case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		break;

	case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		break;

	case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		break;
	}
	*/

	//keyboardEvent.get
	keyboardLabel->setString("Key Pressed");
}

// key up
void OOP::KeyboardListener::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event * event)
{
	cocos2d::EventKeyboard* keyboardEvent = dynamic_cast<cocos2d::EventKeyboard*>(event); // casting as a keyboard event

	/*
	switch (keyCode)
	{
	case cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW:
		break;

	case cocos2d::EventKeyboard::KeyCode::KEY_DOWN_ARROW:
		break;

	case cocos2d::EventKeyboard::KeyCode::KEY_LEFT_ARROW:
		break;

	case cocos2d::EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		break;
	}
	*/

	keyboardLabel->setString("Key Released");
}

// returns the keyboard listener
cocos2d::EventListenerKeyboard * OOP::KeyboardListener::getListener() const { return keyboardListener; }

// returns the label on the keyboard
cocos2d::Label * OOP::KeyboardListener::getLabel() const { return keyboardLabel; }

// toggles the keyboard label on/off
void OOP::KeyboardListener::setLabelVisible() { setLabelVisible(!keyboardLabel->isVisible()); }

// sets whether the label on the keyboard is visible or not.
void OOP::KeyboardListener::setLabelVisible(bool visible) { keyboardLabel->setVisible(visible); }

// sets the position of the keyboard label.
void OOP::KeyboardListener::setLabelPosition(cocos2d::Vec2 newPos) { keyboardLabel->setPosition(newPos); }
