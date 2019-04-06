
#include "SpriteAnimation.h"

//// SPRITE SHEET ANIMATION FRAME CLASS ////
// constructor for sprite animation frame.
OOP::SpriteSheetAnimationFrame::SpriteSheetAnimationFrame(cocos2d::Rect & rect, float delayUnits, int tag)
	: rect(rect), tag(tag)
{
	// this happens outside of the delay units for validation checking.
	setDelayUnits(delayUnits);
}

// returns the rect used for getting a section of the sprite sheet.
cocos2d::Rect OOP::SpriteSheetAnimationFrame::getRect() const { return rect; }

// sets the rect used for etting a section of the sprite sheet.
void OOP::SpriteSheetAnimationFrame::setRect(cocos2d::Rect & rect) { this->rect = rect; }

// returns the amount of delay units.
float OOP::SpriteSheetAnimationFrame::getDelayUnits() const { return delayUnits; }

// sets the amount of delay units. If the value passed is negative, delayUnits is set to zero.
void OOP::SpriteSheetAnimationFrame::setDelayUnits(float delayUnits) { this->delayUnits = (delayUnits >= 0.0F) ? delayUnits : 0.0F; }

// returns the tag attached ot the sprite frame.
int OOP::SpriteSheetAnimationFrame::getTag() const { return tag; }

// sets the tag attached to the sprite frame.
void OOP::SpriteSheetAnimationFrame::setTag(int & tag) { this->tag = tag; }

// sets the primitives tied to the animation frame.
void OOP::SpriteSheetAnimationFrame::setPrimitives(std::vector<OOP::Primitive*>& newPrims) { prims = newPrims; }

// adds a primitive to the animation frame.
void OOP::SpriteSheetAnimationFrame::addPrimitive(OOP::Primitive * prim)
{
	// if it's already in the vector, it won't be added again.
	for(OOP::Primitive * p : prims)
	{
		if (p == prim)
			return;
	}

	prims.push_back(prim);
}

// removes a primitive from the animation frame.
void OOP::SpriteSheetAnimationFrame::removePrimitive(const OOP::Primitive * prim)
{
	// removes the primitive if it exists in the vector.
	for (int i = 0; i < prims.size(); i++)
	{
		if (prims.at(i) == prim) // removes the primitive.
		{
			prims.erase(prims.begin() + i);
			return;
		}
	}
}

// gets the primitives tied to the animation frame.
std::vector<OOP::Primitive*>& OOP::SpriteSheetAnimationFrame::getPrimitives() { return prims; }

// sets whether all of the primitives are active or not.
void OOP::SpriteSheetAnimationFrame::setActivePrimitives(bool active)
{
	for (OOP::Primitive * p : prims)
		p->setActive(active);
}



//////////// SPRITE SHEET ANIMATION CLASS ///////////////////
// sets a sprite sheet only
OOP::SpriteSheetAnimation::SpriteSheetAnimation(cocos2d::Sprite * spriteSheet, unsigned int totalLoops, bool infiniteLoop, float delayUnits, bool sharedDelay, bool restoreOriginalFrame)
	: spriteSheet(spriteSheet), sharedDelay(sharedDelay), restoreOriginalFrame(restoreOriginalFrame)
{
	setLoops(totalLoops);
	setInfiniteLoop(infiniteLoop);
	setDelayUnits(delayUnits);
}

// sets a sprite sheet and the animation frames.
OOP::SpriteSheetAnimation::SpriteSheetAnimation(cocos2d::Sprite * spriteSheet, std::vector<OOP::SpriteSheetAnimationFrame *> & frames, unsigned int totalLoops, bool infiniteLoop, float delayUnits, bool sharedDelay, bool restoreOriginalFrame)
	: spriteSheet(spriteSheet), frames(frames), sharedDelay(sharedDelay), restoreOriginalFrame(restoreOriginalFrame)
{
	// these are set outside of an initialzer list because they require validity checks.
	
	setLoops(totalLoops);
	setInfiniteLoop(infiniteLoop);
}

// gets the amount loops for the sprite sheet animation.
unsigned int OOP::SpriteSheetAnimation::getLoops() const { return totalLoops; }

// sets how many times the animation loops. If the total loops are now less than the amount of loops that have been done, the animation finishes on the next update loop.
void OOP::SpriteSheetAnimation::setLoops(unsigned int totalLoops) { this->totalLoops = totalLoops; }

// returns how many loops have been finished.
unsigned int OOP::SpriteSheetAnimation::getFinishedLoops() const { return finishedLoops; }

// returns whether the animation infinitely loops or not.
bool OOP::SpriteSheetAnimation::getInfiniteLoop() const { return infiniteLoop; }

// toggles the infinite loop on and off.
void OOP::SpriteSheetAnimation::setInfiniteLoop() { setInfiniteLoop(!infiniteLoop); }

// sets whether an animation loops infinitely.
void OOP::SpriteSheetAnimation::setInfiniteLoop(bool infiniteLoop)
{
	if (infiniteLoop) // if the loop is now infinite, then 'loops' is set to 0.
		totalLoops = 0;

	this->infiniteLoop = infiniteLoop;
}

// gets the amount of delay units.
float OOP::SpriteSheetAnimation::getDelayUnits() const { return delayUnits; }

// returns the speed of the animation.
float OOP::SpriteSheetAnimation::getSpeed() const { return speed; }

// sets the speed of the animation. If less than 0, then the speed is set to 1.
void OOP::SpriteSheetAnimation::setSpeed(float speed) { this->speed = (speed > 0.0F) ? speed : 1.0F; }

// gets the opacity based on a percentage (0.0 - 1.0). Uses the same algorithm as the entity class.
float OOP::SpriteSheetAnimation::getOpacity()
{
	return spriteSheet->getOpacity() / 255.0F;
}

// sets the opacity based on a percentage (0.0 - 1.0). Uses the same algorithm as the entity class.
void OOP::SpriteSheetAnimation::setOpacity(float opacity)
{

	if (opacity > 1.0F) // If an opacity greater than 100% (1.0) is provided, the variable is set to 1.0.
	{
		opacity = 1.0F;
	}
	else if (opacity < 0.0F) // If a negative opacity is provided, it is set to 0.
	{
		opacity = 0.0F;
	}

	spriteSheet->setOpacity(255 * opacity); // sets the sprite's new opacity.
}


// flips the animation on the x-axis if a 'true' is passed.
void OOP::SpriteSheetAnimation::setFlippedAnimationX(bool flipX) { this->flipX = flipX; }

// toggles the animation flip on the x-axis
void OOP::SpriteSheetAnimation::setFlippedAnimationX() { setFlippedAnimationX(!flipX); }

// checks if the animation is flipped on the x-axis
bool OOP::SpriteSheetAnimation::getFlippedAnimationX() const { return flipX; }

// flips the animation on the y-axis 
void OOP::SpriteSheetAnimation::setFlippedAnimationY(bool flipY) { this->flipY = flipY; }

// toggles the animation flip on the y-axis
void OOP::SpriteSheetAnimation::setFlippedAnimationY() { setFlippedAnimationY(!flipY); }

// gets whether the animation is flipped on the y-axis or not.
bool OOP::SpriteSheetAnimation::getFlippedAnimationY() const { return flipY; }

// starts playing the animation in reverse by flipping around the vector of frames.
void OOP::SpriteSheetAnimation::reverse() { std::reverse(frames.begin(), frames.end()); }


void OOP::SpriteSheetAnimation::setDelayUnits(float & delayUnits)
{
	// if the delay units passed are less than 0, then the amount of delay units is set to 0.
	this->delayUnits = (delayUnits >= 0.0F) ? delayUnits : 0.0F;
}

// gets whether all frames should have a shared delay.
bool OOP::SpriteSheetAnimation::getSharedDelay() const { return sharedDelay; }

// sets whether all frames should have a shared delay.
void OOP::SpriteSheetAnimation::setSharedDelay(bool sharedDelay) { this->sharedDelay = sharedDelay; }

// gets whether to restore frame 1 once the animation finishes or not.
bool OOP::SpriteSheetAnimation::getRestoreOriginalFrame() const { return restoreOriginalFrame; }

// sets whether to restore frame 1 once the animation finishes or not.
void OOP::SpriteSheetAnimation::setRestoreOriginalFrame(bool restoreFrame1) { restoreOriginalFrame = restoreFrame1; }


// returns the sprite sheet.
cocos2d::Sprite * OOP::SpriteSheetAnimation::getSpriteSheet() const { return spriteSheet; }

// returns the current frame of the animation.
OOP::SpriteSheetAnimationFrame * OOP::SpriteSheetAnimation::getCurrentFrame() const { return frames.at(index); }

// gets the index of the current frame of animation.
unsigned int OOP::SpriteSheetAnimation::getCurrentFrameIndex() const { return index; }

// returns all of the frames in the sprite sheet.
std::vector<OOP::SpriteSheetAnimationFrame*> OOP::SpriteSheetAnimation::getFrames() const { return frames; }

// sets all of the frames in the sprite sheet.
void  OOP::SpriteSheetAnimation::setFrames(std::vector<OOP::SpriteSheetAnimationFrame*> & newFrames) { this->frames = newFrames; }

// adds a frame to the vector
void OOP::SpriteSheetAnimation::add(OOP::SpriteSheetAnimationFrame * newFrame) { *this += newFrame; }

// removes a frame from the vector
void OOP::SpriteSheetAnimation::subtract(OOP::SpriteSheetAnimationFrame * newFrame) { *this -= newFrame; }

// adds a frame to the vector
void OOP::SpriteSheetAnimation::operator+=(OOP::SpriteSheetAnimationFrame * newFrame)
{
	// check to see if the passed frame is already in the vector.
	for (OOP::SpriteSheetAnimationFrame * frame : frames)
	{
		if (frame == newFrame) // if the frame is already in the vector, a void is returned.
			return;
	}

	newFrame->setActivePrimitives(false); // turns off the primitive.
		
	frames.push_back(newFrame); // adds the frame into the vector.
}

// removes a frame from the vector
void OOP::SpriteSheetAnimation::operator-=(OOP::SpriteSheetAnimationFrame * newFrame)
{
	// check to see if the passed frame is in the vector
	for (int i = 0; i < frames.size(); i++)
	{
		if (frames.at(i) == newFrame) // the provided frame has happened.
		{
			frames.erase(frames.begin() + i);
			return; // returns 'void' since the frame has been deleted.
		}
	}

	// if the passed object wasn't found, then nothing happens.
}

// gets a sprite animation frame
OOP::SpriteSheetAnimationFrame * OOP::SpriteSheetAnimation::operator[](const unsigned int index)
{
	// index validation; if the index is out of bounds, a nullptr is returned.
	if (index >= frames.size())
		return nullptr;

	// Returns the frame at the provided index.
	return frames.at(index);
}

// gets the name of the sprite sheet.
std::string OOP::SpriteSheetAnimation::getName() const { return name; }

// gets the name of the sprite sheet.
void OOP::SpriteSheetAnimation::setName(std::string name) { this->name = name; }

// gets the description for the sprite sheet.
std::string OOP::SpriteSheetAnimation::getDescription() const { return description; }

// sets the description for the sprite sheet.
void OOP::SpriteSheetAnimation::setDescription(std::string desc) { this->description = desc; }

// returns a tag for the sprite animation.
int OOP::SpriteSheetAnimation::getTag() const { return tag; }

// sets a tag for the sprite animation.
void OOP::SpriteSheetAnimation::setTag(int tag) { this->tag = tag; }

// gets whether the animation is running or not.
bool OOP::SpriteSheetAnimation::isRunning() { return running; }

// starts the animation from the beginning.
void OOP::SpriteSheetAnimation::runAnimation()
{
	running = true;
	spriteSheet->setTextureRect(frames.at(0)->getRect());
}

// stops an animation. This will cause the animation to return to its start.
void OOP::SpriteSheetAnimation::stopAnimation(bool restoreF1)
{
	running = false;
	paused = false;
	frameTime = false;
	index = 0;
	finishedLoops = 0;

	for (int i = 0; i < frames.size(); i++)
		frames.at(i)->setActivePrimitives(false);

	// if 'restoreF1' is true, then the original frame is restored. If not, the ending frame is restored.
	spriteSheet->setTextureRect((restoreF1) ? frames.at(0)->getRect() : frames[frames.size() - 1]->getRect());
}

// pauses an animation.
void OOP::SpriteSheetAnimation::pauseAnimation() { paused = true; }

// unpauses an animation.
void OOP::SpriteSheetAnimation::unpauseAnimation() { paused = false; }

// updates the sprite animation.
void OOP::SpriteSheetAnimation::update(float deltaTime)
{
	float frameDuration = 0.0F; // the amount of time the frame should be on screen for.

	unsigned int oldIndex = index; // the index upon entering the update loop
	unsigned int newIndex = 0; // the new index when leaving the update loop, which should be one greater than the old index (unless the animation is finished).
	

	if (frames.size() == 0 || spriteSheet == nullptr || paused || !running) // if the animation is paused or isn't running, then the update loop isn't done.
		return;

	// if the sprite sheet does not match up with 'flipX', it is flippd accordingly.
	if (spriteSheet->isFlippedX() != flipX)
		spriteSheet->setFlippedX(flipX);

	// if the sprite sheet does not match up with 'flipY', it is flippd accordingly.
	if (spriteSheet->isFlippedY() != flipY)
		spriteSheet->setFlippedY(flipY);


	frameTime += deltaTime; // adds to the amount of time the frame has existed for.
	
	// if the delay units are shared, then the delay for the sprite sheet animation is used. If not, the delay for the specific frame is used.
	frameDuration = (sharedDelay) ? delayUnits : frames[index]->getDelayUnits();

	// if the frame has been on screen for the proper amount of time or longer, then it moves onto the next frame.
	if (frameTime >= frameDuration / speed) // we divide by 'speed' because we're doing a 'greater than' comparison.
	{
		index++;
		frameTime = 0.0F;
		if (index >= frames.size()) // if the index has surpassed the frame's size, the animation loop is over.
		{
			
			finishedLoops++; // records that a loop has finished, and resets the frameTime.
			index = 0;

			if (finishedLoops >= totalLoops && !infiniteLoop) // if all of the loops have finished, and the animation does not loop infinitly.
			{
				stopAnimation(restoreOriginalFrame); // called to end the animation.
				return;
			}
			else
			{
				spriteSheet->setTextureRect(frames.at(index)->getRect()); // moves onto the next frame.
			}
		}

		newIndex = index;
		
		for (int i = 0; i < frames.at(oldIndex)->getPrimitives().size(); i++) // turns off the primitives for the previous animation frame.
			if(frames.at(index - 1) != nullptr)
				frames.at(index - 1)->getPrimitives().at(i)->setActive(false);

		spriteSheet->setTextureRect(frames.at(index)->getRect()); // moves onto the next nimation frame.

		for (int i = 0; i < frames.at(newIndex)->getPrimitives().size(); i++) // turns on the primitives for the now current animation frame.
			if (frames.at(index - 1) != nullptr)
				frames.at(index - 1)->getPrimitives().at(i)->setActive(true);

	}
}
