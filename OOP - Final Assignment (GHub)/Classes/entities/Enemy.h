#pragma once
#include "entities/Entity.h"

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

		// update loop
		void update(float deltaTime);

		// the position of the player. Used for the A.I.
		static Vec2 playerPos;

	private:

		// called to move the ghost, based on its A.I.
		// void move();

		float view = 0.0F;

	protected:

	} Ghost;
}
