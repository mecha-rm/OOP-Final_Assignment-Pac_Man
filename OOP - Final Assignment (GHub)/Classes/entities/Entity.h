// information for all entities in a scene, which are physical elements part of the game world.
#pragma once

#include "Primitives.h"
#include "Utilities.h"
#include "SpriteAnimation.h"

#include <iostream>
#include <string>

using namespace cocos2d;

namespace entity
{
	// these tags are used to set the identification tags for different entites.
	// these are currently not being used, but they can discern different entities.
	enum etag
	{
		empty = 0,
		block = 1,
		pacdot = 2,
		powerpellet = 3,
		fruit = 4,
		enemy = 5,
		player = 6

	};
	

	class Entity
	{
	public:
		// gets the image of the sprite, what kind of entity it is, andi ts global z order
		Entity(etag tag, std::string texture = "", float globalZOrder = 0.0F);

		virtual ~Entity();

		// gets how long the entity has existed for.
		float getAge();

		// returns the name of the entity.
		const std::string getName() const;

		// returns the description of the entity.
		const std::string getDescription() const;

		// gets the tag that tells the user what kind of entity this is.
		entity::etag getTag();

		// returns the entity's sprite
		Sprite * getSprite() const;

		// returns the image for the sprite
		Texture2D * getTexture() const;

		// gets the file path for the texture.
		std::string getTextureFilePath() const;

		// returns the rectangle used for cropping the texture
		Rect getTextureRect() const;

		// Setting the position. While all sprite children move with the sprite, their positions don't change (i.e. getPosition() for them would return the same value).
		virtual void setPosition(Vec2 newPos);

		// Setting the position
		virtual void setPosition(float x, float y);

		// gets the position of the sprite.
		Vec2 getPosition() const;

		// Setting the sprite's x position.
		virtual void setPositionX(float x);

		// Getting the sprite's x position.
		float getPositionX() const;

		// Setting the sprite's y position.
		virtual void setPositionY(float y);

		// Getting the sprite's y position.
		float getPositionY() const;

		// gets the spawn point of the entity.
		Vec2 getSpawnPosition();

		// sets the spawn position
		void setSpawnPosition(Vec2 spawn);

		// called ot make the entity go back to the spawn position.
		void returnToSpawnPosition();

		// Sets the sprite's opacity via a percentage. Use a value from 0.0 to 1.0, with 1.0 (i.e. 100%) being full opacity.
		// Opacity for sprites are out of 255, but this function works on percentages.
		void setOpacity(float opacity);

		// gets the sprite's current opacity as a value from 0.0 to 1.0 (i.e. a decimal percentage)
		// Opacity for sprites are out of 255, but this function works on percentages.
		float getOpacity();

		// gets rotation factor in degrees (which is what it's stored as).
		float getRotationInDegrees();

		// sets the rotation factor in degrees.
		void setRotationInDegrees(float theta);

		// gets the rotation factor, converted to radians
		float getRotationInRadians();

		// sets the rotation factor in radians
		void setRotationInRadians(float theta);



		// flips the sprite on the x-axis using 'sprFX'. If 'aniFX' is 'true', then the sprite's animations are flipped on the x-axis as well.
		// If 'aniFX' is true, the provided value of 'sprFX' will become the flip factor for ALL ANIMATIONS.
		// in other words, if the sprite is flipped (sprFX == true) and aniFX is 'true', then all of the animation frames would share the same flip factor.
		void setFlippedSpriteX(bool sprFX, bool aniFX = true);

		// flips the sprite on the x-axis. If it was already flipped, it is un-flipped, and vice versa.
		// if aniFX is true, then the animations are also flipped in a similar fashion (if flipped, they become un-flipped, and vice-versa).
		void flipSpriteX(bool aniFX = true);

		// returns 'true' if the sprite is currently flipped on the x-axis. Do note that the current animation may have flip the sprite.
		bool getFlippedSpriteX() const;

		// returns 'true' if all of the sprite animations are flipped, false otherwise.
		bool getFlippedSpriteAnimationsX() const;

		// flips the sprite on the y-axis using 'sprFY'. If 'aniFY' is 'true', then the sprite's animations are flipped on the y-axis as well.
		// If 'aniFY' is true, the provided value of 'sprFY' will become the flip factor for ALL ANIMATIONS.
		// in other words, if the sprite is flipped (sprFX == true) and aniFX is 'true', then all of the animation frames would share the same flip factor.
		void setFlippedSpriteY(bool sprFY, bool aniFY = true);
		
		// flips the sprite on the y-axis. If it was already flipped, it is un-flipped, and vice versa.
		// if aniFx is true, then the animations are also flipped in a similar fashion (if flipped, they become un-flipped, and vice-versa).
		void flipSpriteY(bool aniFX = true);

		// returns 'true' if the sprite is currently flipped on the y-axis. Do note that the current animation may have flipped the sprite.
		bool getFlippedSpriteY() const;

		// returns 'true' if all the sprite animations are flipped, false otherwise.
		bool getFlippedSpriteAnimationsY() const;

		// returns the mass of the entity
		float getMass() const;

		// gets how much force is put into the entity when traveling in a given direction. This will always be positive.
		float getMagnitude() const;

		/*
		 * gets the direction the player is going
			* (0) = no direction; all movements are set to 'false'
			* (1) = up
			* (2) = down
			* (3) = left
			* (4) = right
		*/
		unsigned int getDirection() const;

		/*
		 * sets the direction the entitiy is going. Each entity can only go in one direction at a time.
		 * if 'oneDirec' is 'true', then movement in all other directions is stopped.
			* (0) = no direction; all movements are set to 'false'
				* this is the default if no valid number is given.
			* (1) = up
			* (2) = down
			* (3) = left
			* (4) = right
		*/
		void setDirection(unsigned int direc, bool oneDirec = true);

		// gets the current kind of force applied to the entity.
		// one of these values will always be 0.
		Vec2 getForce() const;

		// gets the force that gets applied on the x-axis
		float getForceX() const;

		// gets the force that gets applied on the y-axis
		float getForceY() const;

		// zeroes out the entity's velocity on both axes
		void stopForce();

		// zeroes out the entity's velocity on the x-axis.
		void stopForceX();

		// zeroes out the entity's velocity on the y-axis.
		void stopForceY();

		// gets the speed of the entity.
		float getSpeed();


		// gets the points given for this entity.
		unsigned int getPoints();

		// sets the amount of points the entity gives.
		void setPoints(unsigned int points);

		// gets the primitive square, which is sued for collisions. This is offset so that it's relative to where it is in the whole world.
		OOP::PrimitiveSquare * getCollisionBody() const;

		// gets the primitive square, offset so that it's where it is relative to the node the player is attactehd to (i.e. relative to their position).
		OOP::PrimitiveSquare * getOffsetCollisionBody() const;

		// gets the collision body offset by the entity's position.
		static OOP::PrimitiveSquare * getOffsetCollisionBody(const entity::Entity * ety, const OOP::PrimitiveSquare * body);

		// gets the primitive square offset by the provided srpite's position.
		static OOP::PrimitiveSquare * getOffsetCollisionBody(const Sprite * spr, const OOP::PrimitiveSquare * body);

		// checks for collision between the entity object and the one passed. This uses the collisionBodies.
		bool collision(entity::Entity * e2);

		// checks for collision between two entities. This uses the collisionBodies vectors for both entities.
		static bool collision(entity::Entity * e1, entity::Entity * e2);

		// returns the vector of animations.
		std::vector<OOP::SpriteSheetAnimation *> getAnimations() const;

		// returns an animation at the provided index. If no animation exists at this index, a 'nullptr' is returned.
		OOP::SpriteSheetAnimation * getAnimationByIndex(unsigned int index) const;

		// gets an animation by a tag. The first animation with this tag will be returned. If an animation with this tag is not found, a nullptr is returned.
		OOP::SpriteSheetAnimation * getAnimationByTag(int tag);

		// returns the index of the animation. If the animation does not exist in the animation vector, then a '-1' is returned.
		int getAnimationIndex(const OOP::SpriteSheetAnimation *) const;

		// gets the current animation being used. If there is no current animation, a nullptr is returned.
		OOP::SpriteSheetAnimation * getCurrentAnimation();

		// adds an animation to the entity. It also returns the index get the animation that has been added.
		void addAnimation(OOP::SpriteSheetAnimation *);

		// runs an animation based on a provided index. If no animation has this index, then no animation is run.
		void runAnimationByIndex(unsigned int index);

		// runs an animation based on a provided tag. If no animation has this tag, no changes are made.
		void runAnimationByTag(int tag);

		// returns 'true' if an animation is currently running, and false otherwise.
		bool runningAnimation();

		// update loop
		virtual void update(float deltaTime);

		// a boolean that toggles on/off hitbox visibility.
		// If you don't want to have some collision shapes visible, set this to 'false', and set specific entities to 'true' or 'false' after initialization.
		static bool shapesVisible;

		bool moveUp = false; // moves the entity up.
		bool moveDown = false; // moves the entity down.
		bool moveLeft = false; // moves the entity left.
		bool moveRight = false; // moves the entity right.

		// the window size of the game pane.
		static Size winSize;

		// saves the position of the entity within the maze, which is its spawnning position.
		Vec2 spawnPos;

	private:
		// the image path of the entity. Can be used to create another texture.
		std::string imagePath = "";
		
		float mass = 1.0; // the mass of the entity
		float magnitude = 0.0F; // the magnitude of the movement, i.e. how much the entity moves.
		float speed = 1.0F; // the speed of the entity
		
		// the amount of points provided by the entity.
		unsigned int points = 0;

		float age = 0; // gets the length of time the entity has existed for, in milliseconds (delta time)

		

	protected:

		// sets the name of the entity.  This also gets stored as the sprite name.
		void setName(std::string name);

		// sets the description of the entity.
		void setDescription(std::string description);
		
		// sets the tag for the entity
		void setTag(entity::etag tag);

		// the name of the entity
		std::string name;

		// the description of the entity
		std::string description;

		// sets the sprite for the entity
		void setSprite(Sprite * sprite);

		// sets the sprite's texture (image)
		void setTexture(std::string image);

		// sets the sprite's textureRect; i.e. the area of the sprite's that's actually used.
		// 'Rects' are based off a start point and end point.
		void setTextureRect(Rect textureRect);

		// sets the sprite's texture rect, i.e. the area of the sprite's image file that's used.
		// (x, y) and (width, height) act as starting points and ending points respectively
		// if USE_CENTRE is true, then the cropped area treats (x, y) as the centre of the area, rather than the corner of the area.
		void setTextureRect(float x, float y, float width, float height, const bool USE_CENTRE = false);
		
		// sets the mass of the entity; it must be greater than 0.
		void setMass(float mass);

		// sets magnitude
		void setMagnitude(float magnitude);

		// sets the speed of the entity, If a speed less than 0 is provided, the speed is set to 1.0F.
		void setSpeed(float speed);

		// sets a vector for collision bodies for the entity.
		void setCollisionBody(OOP::PrimitiveSquare * newBody);

		Sprite * sprite; // the entity's sprite
		Rect frameSize = Rect(0.0F, 0.0F, 32.0F, 32.0F); // the size of an individual frame of the sprite.

		std::vector<OOP::SpriteSheetAnimation *> animations; // a vector of animations.

		OOP::SpriteSheetAnimation * currentAnimation = nullptr; // saves a pointer to the current animation being run.

		// the collision body for the
		OOP::PrimitiveSquare * colBody = nullptr;
	};
}



