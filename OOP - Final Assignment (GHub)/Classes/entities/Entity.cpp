#include "entities/Entity.h"
#include "Utilities.h"

bool entity::Entity::shapesVisible = false; // change this to 'false' to hide all collision shapes from view.
Size entity::Entity::winSize = Size::ZERO; // the size of the window

entity::Entity::Entity(etag tag, std::string texture, float globalZOrder) : sprite(Sprite::create())
{
	imagePath = texture;
	sprite->setTexture(texture);
	sprite->setAnchorPoint(Vec2(0.5, 0.5)); // anchour point is the middle of the sprite
	sprite->setGlobalZOrder(globalZOrder); // setting the global z order
	sprite->setTag(tag);
	// sprite->setTag(entity);
}

// releases the sprite 
entity::Entity::~Entity() 
{
	colBody->getPrimitive()->removeFromParent(); // removes the image form its parent.
	sprite->removeFromParent(); // removes the sprite from its parent.	
}

// returns the length of time the entity has existed for.
float entity::Entity::getAge() { return age; }

// returns the entity's name.
const std::string entity::Entity::getName() const { return name; }

// sets the entity's name in the sprite.
void entity::Entity::setName(std::string name)
{
	this->name = name;
	sprite->setName(name);
}

// Returns the entity's description.
const std::string entity::Entity::getDescription() const { return description; }

// sets the description of the entity.
void entity::Entity::setDescription(std::string description) { this->description = description; }

// gets entity's tag
entity::etag entity::Entity::getTag() { return (entity::etag)sprite->getTag(); }

// sets entity's tag
void entity::Entity::setTag(entity::etag tag) { sprite->setTag((int)tag); }

// returns the entity's sprite
Sprite * entity::Entity::getSprite() const { return sprite; }

// sets the entity's sprite
void entity::Entity::setSprite(Sprite * sprite) { this->sprite = sprite; }

// returns the sprite's texture (image)
Texture2D * entity::Entity::getTexture() const { return sprite->getTexture(); }

// sets the entity's texture via an image path
void entity::Entity::setTexture(std::string image) {
	imagePath = image;
	sprite->setTexture(image);
}

// gets the texture file path.
std::string entity::Entity::getTextureFilePath() const { return imagePath; }

// returns hte texture rect used to crop the sprite's image
Rect entity::Entity::getTextureRect() const { return sprite->getTextureRect(); }

// sets the textureRect (cropped area) for the sprite
void entity::Entity::setTextureRect(Rect textureRect) { sprite->setTextureRect(textureRect); }

// sets the textureRect(cropped area) for the sprite
void entity::Entity::setTextureRect(float x, float y, float width, float height, const bool USE_CENTRE)
{
	// USE_CENTRE == TRUE -> if the user wants (x, y) to be the centre point of the tecture rect
	// USE_CENTRE == FALSE -> if the user wants (x, y) to be a corner point
	(USE_CENTRE) ? setTextureRect(Rect(x - width / 2, y - width / 2, width, height)) : setTextureRect(Rect(x, y, width, height));
}


// sets the entity's position. While all sprite children move with the sprite, their positions don't change (i.e. getPosition() for them would return the same value).
void entity::Entity::setPosition(Vec2 newPos)  { sprite->setPosition(newPos); }

// sets the entity's position
void entity::Entity::setPosition(float x, float y) { setPosition(Vec2(x, y)); }

// Gets the position of the sprite
Vec2 entity::Entity::getPosition() const { return sprite->getPosition(); }

void entity::Entity::setPositionX(float x) { setPosition(x, sprite->getPositionY()); }

// gets the sprite's x position.
float entity::Entity::getPositionX() const { return sprite->getPositionX(); }

void entity::Entity::setPositionY(float y) { setPosition(sprite->getPositionX(), y); }

// gets the sprite's y position.
float entity::Entity::getPositionY() const { return sprite->getPositionY(); }

// gets the spawn position of the entity.
Vec2 entity::Entity::getSpawnPosition() { return spawnPos; }

// sets the spawn position of the entity
void entity::Entity::setSpawnPosition(Vec2 spawn) { spawnPos = spawn; }

// called ot make the entity go back to the spawn position.
void entity::Entity::returnToSpawnPosition()
{
	setPosition(spawnPos);
}



// sets the opacity of the sprite via a percentage.
void entity::Entity::setOpacity(float opacity)
{
	// If an opacity greater than 100% (1.0) is provided, the variable is set to 1.0.
	if (opacity > 1.0F)
	{
		opacity = 1.0F;

		// If a negative opacity is provided, it is set to 0.
	}
	else if (opacity < 0.0F)
	{
		opacity = 0.0F;
	}

	sprite->setOpacity(255 * opacity); // sets the sprite's new opacity.
}

// gets the sprite's opacity as a percentage.
float entity::Entity::getOpacity() { return sprite->getOpacity() / 255.0F; }

// gets rotation factor in degrees, which is what it's stored as.
float entity::Entity::getRotationInDegrees() { return sprite->getRotation(); }

// gets rotation factor in radians
void entity::Entity::setRotationInDegrees(float theta) { sprite->setRotation(theta); }

// gets the rotation factor in radians.
float entity::Entity::getRotationInRadians() { return umath::degreesToRadians(sprite->getRotation()); }

// sets the rotation factor in radians
void entity::Entity::setRotationInRadians(float theta) { sprite->setRotation(umath::radiansToDegrees(theta)); }

// flips the sprite based on the value of sprFX. If 'aniFX' is 'true', then all of the animations are given this flip factor as well.
void entity::Entity::setFlippedSpriteX(bool sprFX, bool aniFX)
{
	sprite->setFlippedX(sprFX); // flips the sprite

	if (aniFX)
	{
		for (OOP::SpriteSheetAnimation * sprA : animations) // flips all of the animations.
			sprA->setFlippedAnimationX(sprFX);	
	}
}

// flips the sprite on the x-axis. If it was already flipped, it is un-flipped, and vice versa.
// if aniFX is true, then the animations are also flipped in a similar fashion (if flipped, they become un-flipped, and vice-versa).
void entity::Entity::flipSpriteX(bool aniFX)
{
	sprite->setFlippedX(!sprite->isFlippedX()); // makes the flip factor the opposite of what it currently is.

	if (aniFX)
	{
		for (OOP::SpriteSheetAnimation * sprA : animations) // reverses the current animation flip (if flipped, they become unflipped and vice versa).
			sprA->setFlippedAnimationX(!sprA->getFlippedAnimationX());
	}
}

// returns 'true' if the sprite is currently flipped on the x-axis. Do note that the current animation may have flip the sprite.
bool entity::Entity::getFlippedSpriteX() const { return sprite->isFlippedX(); }

// returns 'true' if all of the sprite animations are flipped, false otherwise.
bool entity::Entity::getFlippedSpriteAnimationsX() const
{
	for (OOP::SpriteSheetAnimation * sprAni : animations)
	{
		if (!sprAni->getFlippedAnimationX()) // if the sprite isn't flipped, then a 'false' is returned.
			return false;
	}

	return true;
}

// flips the sprite on the y-axis using 'sprFY'. If 'aniFY' is 'true', then the sprite's animations are flipped on the y-axis as well.
// If 'aniFY' is true, the provided value of 'sprFY' will become the flip factor for ALL ANIMATIONS.
// in other words, if the sprite is flipped (sprFX == true) and aniFX is 'true', then all of the animation frames would share the same flip factor.
void entity::Entity::setFlippedSpriteY(bool sprFY, bool aniFY)
{
	sprite->setFlippedY(sprFY); // flips the sprite

	if (aniFY)
	{
		for (OOP::SpriteSheetAnimation * sprA : animations) // flips all of the animations.
			sprA->setFlippedAnimationY(sprFY);
	}
}

// flips the sprite based on the value of sprFY. If 'aniFY' is 'true', then all of the animations are given this flip factor as well.
void entity::Entity::flipSpriteY(bool aniFX)
{
	sprite->setFlippedY(!sprite->isFlippedY()); // makes the flip factor the opposite of what it currently is.

	if (aniFX)
	{
		for (OOP::SpriteSheetAnimation * sprA : animations) // reverses the current animation flip (if flipped, they become unflipped and vice versa).
			sprA->setFlippedAnimationY(!sprA->getFlippedAnimationY());
	}
}

// returns 'true' if the sprite is currently flipped on the y-axis. Do note that the current animation may have flip the sprite.
bool entity::Entity::getFlippedSpriteY() const { return sprite->isFlippedY(); }

// returns 'true' if all the sprite animations are flipped, false otherwise.
bool entity::Entity::getFlippedSpriteAnimationsY() const
{
	for (OOP::SpriteSheetAnimation * sprAni : animations)
	{
		if (!sprAni->getFlippedAnimationY()) // if the sprite isn't flipped, then a 'false' is returned.
			return false;
	}

	return true;
}


// returns the mass of the entity
float entity::Entity::getMass() const { return mass; }

// sets the mass of the entity; can't be below or equal to 0.
void entity::Entity::setMass(float mass) { (mass > 0.0F) ? this->mass = mass : this->mass; }

// gets the magnitude of the entity's movement
float entity::Entity::getMagnitude() const { return magnitude; }

// gets the direction of the entity
// 0 = no direction, 1= up, 2 = down, 3 = left, 4 = right
unsigned int entity::Entity::getDirection() const
{
	// checks to see if any of the variables are true, and returns the number accordingly.
	if (moveUp)
		return 1;

	if (moveDown)
		return 2;

	if (moveLeft)
		return 3;

	if (moveRight)
		return 4;

	return 0;
}

// sets the direction of the entity.
// 0 = no direction, 1= up, 2 = down, 3 = left, 4 = right
void entity::Entity::setDirection(unsigned int direc, bool oneDirec)
{
	// disables all directions first
	if (oneDirec)
	{
		moveUp = false;
		moveDown = false;
		moveLeft = false;
		moveRight = false;
	}

	switch (direc) // sets player direction.
	{
	case 1: // up
		moveUp = true;
		break;

	case 2: // down
		moveDown = true;
		break;

	case 3: // left
		moveLeft = true;
		break;

	case 4: // right
		moveRight = true;
		break;
	}
}

// sets hte magnitude of the entity
void entity::Entity::setMagnitude(float magnitude) { this->magnitude = magnitude; }

// returns the force on both axes
Vec2 entity::Entity::getForce() const { 
	Vec2 tempForce;

	tempForce.x = magnitude * (moveRight == true) ? abs(magnitude) : (moveLeft == true) ? -abs(magnitude) : 0.0F; // sets force on the x-axis
	tempForce.y = magnitude * (moveUp == true) ? abs(magnitude) : (moveDown == true) ? -abs(magnitude) : 0.0F; // sets force on the y-axis

	return tempForce;
}

// returns the force on the x-axis
float entity::Entity::getForceX() const { return getForce().x; }

// returns the force on the y-axis
float entity::Entity::getForceY() const { return getForce().y; }


// stops the force on both the x and the y-axis.
void entity::Entity::stopForce()
{ 
	stopForceX();
	stopForceY();
}

// stops force on the x-axis for the entity.
void entity::Entity::stopForceX() 
{
	moveLeft = false;
	moveRight = false;
}

// stops y-axis movement
void entity::Entity::stopForceY()
{
	moveUp = false;
	moveDown = false;
}

// gets hte speed of the entity.
float entity::Entity::getSpeed() { return speed; }

// setting the speed of the entity. If a speed less than 0.0F, then it's set to 1.
void entity::Entity::setSpeed(float speed) { this->speed = (speed > 0.0F) ? speed : 1.0F; }

// gets the points given for this dot.
unsigned int entity::Entity::getPoints() { return points; }

// sets the amount of points the entity gives.
void entity::Entity::setPoints(unsigned int points) { this->points = points; }



// sets the collision body of the entity.
void entity::Entity::setCollisionBody(OOP::PrimitiveSquare * newColBody)
{
	// if(colBody != nullptr && colBody->getPrimitive()->getParent() != nullptr)
		// colBody->getPrimitive()->removeFromParent(); // removes the colBody from the sprite
	
	// delete colBody;
	
	colBody = newColBody;
	sprite->addChild(colBody->getPrimitive()); // adds the new colBody to the scene.
}

// gets the collision body for the entity.
OOP::PrimitiveSquare * entity::Entity::getCollisionBody() const { return colBody; }

// gets the collision body, offset by the entity's position.
OOP::PrimitiveSquare * entity::Entity::getOffsetCollisionBody() const { return getOffsetCollisionBody(this, colBody); }

// gets the collision body, offset by the entity's position.
OOP::PrimitiveSquare * entity::Entity::getOffsetCollisionBody(const entity::Entity * ety, const OOP::PrimitiveSquare * body)
{
	if (ety == nullptr || body == nullptr)
		return nullptr;

	return getOffsetCollisionBody(ety->getSprite(), body);
}

// gets the collision body, offset by the entity's position.
OOP::PrimitiveSquare * entity::Entity::getOffsetCollisionBody(const Sprite * spr, const OOP::PrimitiveSquare * body)
{
	OOP::PrimitiveSquare * newPrim; // the new primitive.

	if (spr == nullptr || body == nullptr) // handles empty values.
		return nullptr;

	// eBl gets the 'bottom left-hand corner' of the sprite, which is considered its origin.
	Vec2 eBl(spr->getPositionX() - spr->getTextureRect().size.width / 2, spr->getPositionY() - spr->getTextureRect().size.height / 2);

	newPrim = new OOP::PrimitiveSquare(eBl + body->getPosition(), body->m_WIDTH, body->m_HEIGHT); // makes the new primitive.

	return newPrim;
}

// checks for collision with the current entity and a passed entity.
bool entity::Entity::collision(entity::Entity * e2) { return collision(this, e2); }

// checks for collisions using collision bodies
bool entity::Entity::collision(entity::Entity * e1, entity::Entity * e2) { return OOP::Primitive::collision(e1->getCollisionBody(), e2->getCollisionBody()); }


// gets the animations for the entity.
std::vector<OOP::SpriteSheetAnimation *> entity::Entity::getAnimations() const { return animations; }

// returns the animation at the provided index.
OOP::SpriteSheetAnimation * entity::Entity::getAnimationByIndex(unsigned int index) const
{
	// if the index is outside of the size of 'animations', then a nullptr is immediately returned.
	return (index < animations.size()) ? animations.at(index) : nullptr;
}

// gets an animation by a tag. The first animation with this tag will be returned. If an animation with this tag is not found, a nullptr is returned.
OOP::SpriteSheetAnimation * entity::Entity::getAnimationByTag(int tag)
{
	for (OOP::SSAnimation * ani : animations)
	{
		if (ani->getTag() == tag)
			return ani;
	}

	return nullptr;
}

// returns the index of the passed animation. If the animation does not exist in the vector, a '-1' is returned.
int entity::Entity::getAnimationIndex(const OOP::SpriteSheetAnimation * anime) const
{
	for (int i = 0; i < animations.size(); i++) // checks all indexes
	{
		if (animations.at(i) == anime)
			return i;
	}
	return -1;
}

// returns the current animation. If there is no current animation, a nullptr is returned.
OOP::SpriteSheetAnimation * entity::Entity::getCurrentAnimation() { return currentAnimation; }

// adds an animation to the entity, and returns the index of said animation.
void entity::Entity::addAnimation(OOP::SpriteSheetAnimation * newAnimation)
{
	animations.push_back(newAnimation);
}

// runs an animation based on a provided index. If no animation has this index, then no animation is run.
void entity::Entity::runAnimationByIndex(unsigned int index)
{
	if (index >= animations.size()) // index out of bounds
		return;

	if (currentAnimation != nullptr) // stops the current animation if there is one.
		currentAnimation->stopAnimation();

	currentAnimation = animations.at(index);
	currentAnimation->runAnimation(); // runs the new animation.
}

// runs the animation by the provided tag.
void entity::Entity::runAnimationByTag(int tag)
{
	int index = -1;

	for (int i = 0; i < animations.size(); i++)
	{
		if (animations.at(i)->getTag() == tag) // an animation has been found.
		{
			index = i;
			break;
		}
	}

	if (index >= 0) // if an animation has been found.
		runAnimationByIndex(index);
}

// returns 'true' if an animation is running, false otherwise.
bool entity::Entity::runningAnimation() { return currentAnimation->isRunning(); }




// Update Loop; used for movment.
void entity::Entity::update(float deltaTime)
{
	Vec2 position = getPosition(); // gets the entity's current position
	Vec2 acceleration; // the enemy's current acceleration
	Vec2 force;

	// force.x = addForce();

	force = getForce(); // gets the force that should be applied.

	acceleration = force / mass; // gets the force to be applied, divided by the entity's mass.

	position += acceleration * speed * deltaTime; // increase the position by the provided velocity.

	setPosition(position); // sets the entity's new position

	// screen wrapping (x-axis)
	if (getPositionX() < 0.0F - colBody->m_WIDTH / 2.0F) // if the entity has left the window from the left side, they respawn on the right.
	{
		setPositionX(winSize.width + colBody->m_WIDTH / 2.0F);
	}
	else if (getPositionX() > winSize.width + colBody->m_WIDTH / 2.0F) // leaving the screen from the right.Reappears on the left.
	{
		setPositionX(0.0F - colBody->m_WIDTH / 2.0F);
	}

	// screen wrapping (y-axis)
	if (getPositionY() < 0.0F - colBody->m_HEIGHT / 2.0F) // if the entity has left the window from the left side, they respawn on the right.
	{
		setPositionY(winSize.height + colBody->m_HEIGHT / 2.0F);
	}
	else if (getPositionY() > winSize.height + colBody->m_HEIGHT / 2.0F) // leaving the screen from the right.Reappears on the left.
	{
		setPositionY(0.0F - colBody->m_HEIGHT / 2.0F);
	}

	// if there is an animation being run, then the update loop is called.
	if (currentAnimation != nullptr)
		currentAnimation->update(deltaTime);

	age += deltaTime; // counts how long an entity has existed for.
}
