/*
* Project: Object Oriented Programming - Final Project - PAC-MAN
* Date: 04/06/2019

* Group Members: Assignment Group 6
	- Caleb Birnie (100699828)
	- Nathan Tuck (100708651)
	- Roderick “R.J.” Montague (100701758)
	- Ryan Burton (100707511)
	- Tavis East (100702011)

*/
#pragma once
#include "entities/Entity.h"
#include "Maze.h"

namespace entity
{
	typedef class Enemy : public entity::Entity
	{
	public:
		/*
		 * creates an enemy; Clyde is the default.
		 * The options are shown below, and what their habits were in the original PAC-MAN
			- [1] = Blinky (Red) - chased Pac-Man down directly.
			- [2] = Pinky (Pink) - attempts to ambush Pac-Man by moving parallel to him to try and cut him off.
			- [3] = Inky (Blue) - follows Pac-Man part of the time, usually when other ghosts are around.
			- [4] = Clyde (Orange) - goes wherever he wants basically.	
		*/
		Enemy(unsigned short int ghost);

		~Enemy();

		// makes the enemy stall for a predetermined amount of time.
		void wait();

		// makes the enemy stall for (x) amount of time
		void wait(float time);
		
		// called to indiciate if blue mode is on or off.
		void blueMode(bool bMode);

		// update loop
		void update(float deltaTime);

		
		// static Maze * maze;

		// the position of the player. Used for the A.I.
		static Vec2 playerPos;

		bool inPen = true; // the ghost is in the pen.


	private:

		// called to move the ghost, based on its A.I.
		// void move();

		float view = 0.0F;

		float waitTimer = 0.0F; // must countdown to '0' before the enemy can move
		float WaitTimeMax = 2.0F; // the amount of time the enemy must wait.

	protected:

	} Ghost;
}
