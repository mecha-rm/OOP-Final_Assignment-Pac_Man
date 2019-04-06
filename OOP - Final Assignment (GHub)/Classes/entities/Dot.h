// Used for pac-dots and power pellets
#pragma once

#include "entities/Entity.h"

namespace entity
{
	// the dots Pac-Man eats.
	typedef class Dot : public entity::Entity
	{
	public:
		Dot();
		~Dot();

		// update loop
		void update(float deltaTime);

	private:
		unsigned int points;

	protected:
		// a protected constructor to be used exclusively by the pellet to set its proper tag
		Dot(entity::etag tag);

	} PacDot;

	// the pellets that end up turning the ghosts blue
	typedef class Pellet : public Dot
	{
	public:
		Pellet();
		~Pellet();

		// update loop
		void update(float deltaTime);

	private:

	protected:


	} PowerPellet;
}
