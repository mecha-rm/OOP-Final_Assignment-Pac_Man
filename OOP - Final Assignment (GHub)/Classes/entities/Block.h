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

