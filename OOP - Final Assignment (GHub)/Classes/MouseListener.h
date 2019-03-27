// Used for making a mouse.
#pragma once
#include "cocos2d.h"

namespace OOP
{
	// Question 3: MouseListener Class
	class MouseListener
	{
	public:
		// Member Functions
		MouseListener(cocos2d::Scene *); // including HelloWorldScene.h caused an infinite inclusion problem, so cocos2d::Scene is included instead.
		~MouseListener();

		// Question 4: function Implementation 
		void OnMouseDown(cocos2d::Event * a_Event);

		void OnMouseUp(cocos2d::Event * event);

		void OnMouseMove(cocos2d::Event * a_Event);

		void OnMouseScroll(cocos2d::Event * a_Event);

		void OnMouseCallback(cocos2d::Event * a_Event);

		cocos2d::EventListenerMouse * getListener() const;

		// returns the button pressed on the mouse.
		cocos2d::EventMouse::MouseButton getMouseButton() const;

		// returns true of the mouse is being held down, false otherwised.
		bool getMouseButtonDown() const;

		// returns the mouse's current position
		cocos2d::Vec2 getMousePosition() const;
		
		// returns the position of the mouse when it last clicked.
		cocos2d::Vec2 getMouseClickPosition() const;

		// returns the mouse's label
		cocos2d::Label * getLabel();

		// toggle for mouse label visibility.
		void setLabelVisible();

		// sets the visibility of the mouse's label; off by default.
		void setLabelVisible(bool visible);

		// sets the position of the mouse's label
		void setLabelPosition(cocos2d::Vec2 newPos);

	private:
		// Member Variables
		cocos2d::Scene * scene;
		cocos2d::Label * mouseLabel; // label for mouse actions
		cocos2d::EventListenerMouse * mouseListener; // mouse listener

		cocos2d::EventMouse::MouseButton mouseButton; // saves the most recent mouse button pressed or released.
		bool mouseButtonDown = false; // becomes 'true' when the mouse has been held down. It becomes 'false' when the mouse button has been released.

		cocos2d::Vec2 mouseClickPosition; // saves what the click position of the mouse last was.
		cocos2d::Vec2 mousePosition; // saves the location of the mouse.

	protected:
	};
}

