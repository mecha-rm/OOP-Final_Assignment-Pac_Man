#pragma once
#include "cocos2d.h"

namespace OOP
{
	class KeyboardListener
	{
	public:
		KeyboardListener(cocos2d::Scene * scene);

		~KeyboardListener();

		// a key has been pressed
		void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

		// a key has been released
		void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

		cocos2d::EventListenerKeyboard * getListener() const;

		// returns the mouse's label
		cocos2d::Label * getLabel() const;

		// toggle for mouse label visibility.
		void setLabelVisible();

		// sets the visibility of the mouse's label; off by default.
		void setLabelVisible(bool visible);

		// sets the position of the mouse's label
		void setLabelPosition(cocos2d::Vec2 newPos);

		// Member Variables
		cocos2d::Scene * scene;
		cocos2d::Label * keyboardLabel; // label for mouse actions
		cocos2d::EventListenerKeyboard * keyboardListener; // mouse listener
	};
}

