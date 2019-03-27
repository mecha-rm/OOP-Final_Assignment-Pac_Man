#include <iostream>
#include <string>

// Object Oriented Programming - Lab 2 | Member Functions - Mouse Events
// Question 1: MouseListener Source
#include "MouseListener.h"

// Initializer list
OOP::MouseListener::MouseListener(cocos2d::Scene * scene) : mouseListener(cocos2d::EventListenerMouse::create())
{
	// Both callback methods due the same thing.
	mouseListener->onMouseDown = CC_CALLBACK_1(OOP::MouseListener::OnMouseDown, this); // an alternate way to create a callback from the way shown below
	mouseListener->onMouseUp = CC_CALLBACK_1(OOP::MouseListener::OnMouseUp, this); // creates the callback
	mouseListener->onMouseMove = std::bind(&OOP::MouseListener::OnMouseMove, this, std::placeholders::_1); // creates the callback
	mouseListener->onMouseScroll = std::bind(&OOP::MouseListener::OnMouseScroll, this, std::placeholders::_1); // creates the callback

	
	mouseLabel = cocos2d::Label::create("Hello", "fonts/arial.ttf", 30); // creates the label
	mouseLabel->setGlobalZOrder(100.2F); // the mouse label should be in front of everything.
	mouseLabel->setPosition(cocos2d::Vec2(650.0F, 500.0F)); // repositioning the label
	mouseLabel->setVisible(true); // making hte label not visible
	
	this->scene = scene; // sets the mouse's scene to that of the one passed.
	this->scene->getEventDispatcher()->addEventListenerWithFixedPriority(mouseListener, 1); // adds the mouse listener to the passed scene.
	this->scene->addChild(mouseLabel); // adds the label to the scene.
	

	// 	getEventDispatcher()->addEventListenerWithFixedPriority(mouse.getListener(), 1); // adds a mouse listener to the scene using the event dispatcher. It has a priority of 1.
	// mouse.getListener()->setEnabled(ENABLE_MOUSE); // sets whether the mouse is enabled or not.
}


// Question 6: releases the event mouse listener
OOP::MouseListener::~MouseListener() 
{ 
	scene->getEventDispatcher()->removeEventListener(mouseListener);
	/*mouseListener->release();*/ }

// Question 4: onMouseDown Function
void OOP::MouseListener::OnMouseDown(cocos2d::Event * a_Event)
{
	cocos2d::EventMouse* mouseEvent = dynamic_cast<cocos2d::EventMouse*>(a_Event); // casts as mouse event.

	mouseClickPosition = mouseEvent->getLocationInView(); // gets the mouse position; this may need to be offset depending on where the window is.
	mouseButton = mouseEvent->getMouseButton(); // gets the mouse button from the event handler.
	mouseButtonDown = true; // button is being held.
	mouseLabel->setPosition(mouseClickPosition); // changes the position of the label.

	/*
	// left is pressed.
	if (mouseButton == cocos2d::EventMouse::MouseButton::BUTTON_LEFT)
	{

	}
	// middle is pressed.
	else if (mouseButton == cocos2d::EventMouse::MouseButton::BUTTON_MIDDLE)
	{

	}
	// right is pressed.
	else if (mouseButton == cocos2d::EventMouse::MouseButton::BUTTON_RIGHT)
	{

	}
	*/

	// std::cout << "On Mouse Down" << std::endl;
	mouseLabel->setString("MouseDown");

}

void OOP::MouseListener::OnMouseUp(cocos2d::Event * a_Event)
{
	cocos2d::EventMouse* mouseEvent = dynamic_cast<cocos2d::EventMouse*>(a_Event); // casts as mouse event.

	mouseClickPosition = mouseEvent->getLocationInView(); // gets the mouse position; this may need to be offset depending on where the window is.
	mouseButton = mouseEvent->getMouseButton(); // gets the mouse button from the event handler that has been let go.
	mouseButtonDown = false; // button has been let go.
	
	// std::cout << "On Mouse Up" << std::endl;
	mouseLabel->setString("MouseUp");
}

void OOP::MouseListener::OnMouseMove(cocos2d::Event * a_Event)
{
	cocos2d::EventMouse* mouseEvent = dynamic_cast<cocos2d::EventMouse*>(a_Event); // casts as mouse event.
	mousePosition = mouseEvent->getLocationInView(); // gets the mouse's current position.

	// std::cout << "On Mouse Move" << std::endl;
	mouseLabel->setString("MouseMove");
}

void OOP::MouseListener::OnMouseScroll(cocos2d::Event * a_Event)
{

	// std::cout << "On Mouse Scroll" << std::endl;
	mouseLabel->setString("MouseScroll");
}


void OOP::MouseListener::OnMouseCallback(cocos2d::Event * a_Event)
{
	// std::cout << "OnMouseCallback" << std::endl;
	mouseLabel->setString("MouseCallback");
}

// returns the mouse listener
cocos2d::EventListenerMouse * OOP::MouseListener::getListener() const { return mouseListener; }

// returns the most recent mouse button that has been pressed.
cocos2d::EventMouse::MouseButton OOP::MouseListener::getMouseButton() const { return mouseButton; }

// returns whether a mouse button is being held down or not.
bool OOP::MouseListener::getMouseButtonDown() const { return mouseButtonDown; }

// returns the mouse's current position
cocos2d::Vec2 OOP::MouseListener::getMousePosition() const { return mousePosition; }

// returns the position of the mouse's click
cocos2d::Vec2 OOP::MouseListener::getMouseClickPosition() const { return mouseClickPosition; }

// returns the label attached to the mouse.
cocos2d::Label * OOP::MouseListener::getLabel() { return mouseLabel; }

// toggle for mouse label visibility
void OOP::MouseListener::setLabelVisible() { setLabelVisible(!mouseLabel->isVisible()); }

// sets label visibility.
void OOP::MouseListener::setLabelVisible(bool visible) { mouseLabel->setVisible(visible); }

// sets the position of the label.
void OOP::MouseListener::setLabelPosition(cocos2d::Vec2 newPos) { mouseLabel->setPosition(newPos); }


