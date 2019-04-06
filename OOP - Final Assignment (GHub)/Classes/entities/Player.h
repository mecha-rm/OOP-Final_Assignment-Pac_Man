// the class for the player, being Pac-Man
#pragma once
#include "entities/Entity.h"

namespace entity
{
	typedef class Player : public Entity
	{
	public:
		Player();
		~Player();

		
		
		void update(float deltaTime);

	private:
		float score;
		unsigned int lives;
		

	protected:
		
	} PacMan;
}