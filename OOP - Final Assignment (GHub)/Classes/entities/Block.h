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
// Used to make walls in the program

#include "entities/Entity.h"

#pragma once

namespace entity
{
	class Block : public entity::Entity
	{
	public:
		// sets the position of the block.
		Block(Vec2 pos = Vec2(0.0F, 0.0F));

		// sets the position of the block with individual values.
		Block(float x, float y);

		~Block();

		// update loop
		void update(float deltaTime);

	private:

	protected:

	};
}

