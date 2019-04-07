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

		// gets the player's score
		unsigned int getScore();

		// sets the player's score
		void setScore(unsigned int newScore);

		// adds points to the player's score
		void addPoints(unsigned int points);

		// gets the amount of lives the player has.
		unsigned int getLives();

		// sets the amount of lives the player has.
		void setLives(unsigned int lifeCount);

		// called to indiciate if blue mode is on or off.
		void blueMode(bool bMode);

		// called to make the player lose a life. Nothing happens if the player has no lives left.
		void kill();

		
		void update(float deltaTime);

		unsigned int LIVES_MAX = 3; // the maximum amount of lives hte player has.

	private:
		unsigned int score = 0;
		unsigned int lives = 0;

		
		

	protected:
		
	} PacMan;
}