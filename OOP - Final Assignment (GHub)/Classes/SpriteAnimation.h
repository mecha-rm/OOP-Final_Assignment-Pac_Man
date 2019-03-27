// a class used for animating a sprite sheet
#pragma once

#include "cocos/2d/CCSprite.h"
#include "cocos/math/CCGeometry.h"

#include "Primitives.h";

#include <iostream>
#include <string>
#include <vector>

namespace OOP
{
	typedef class SpriteSheetAnimationFrame // an individual frame of animation
	{
	public:
		/*
		 * creates a sprite sheet animation frame using a texture rect and a number of delay units.
		 * if there are no delayUnits, the animation will move onto the next frame the following update.
		 * if no tag is provided, a tag of '0' is set. 
		*/
		SpriteSheetAnimationFrame(cocos2d::Rect & rect, float delayUnits = 0.0F, int tag = 0);

		// returns the rectangle that's used to crop the sprite sheet.
		cocos2d::Rect getRect() const;

		// sets the rectangle used to get an image out of the sprite sheet.
		// for a sprite sheet, the location (x, y) is the top left corner of the rect, and the width and height are the bottom right corner.
		void setRect(cocos2d::Rect & rect);

		// gets how long this sprite frame remains active (in milliseconds).
		float getDelayUnits() const;

		// sets how long this sprite frame remains active (in milliseconds).
		// if this is set to '0', then the animation will move onto the next frame upon the next update.
		void setDelayUnits(float delayUnits);

		// gets the tag for the sprite sheet frame.
		int getTag() const;

		// sets the tag for the sprite sheet frame. This can be used for identification.
		void setTag(int & tag);

		// sets the primitves for the animation frame. These primitives will be turned on when the animation frame is viewable, and off when it isn't.
		void setPrimitives(std::vector<OOP::Primitive *> & newPrims);

		// gets the primitives tied to the animation frame.
		std::vector<OOP::Primitive *> & getPrimitives();

		// sets whether the primitives are active or not.
		void setActivePrimitives(bool active);
		
		int tag; // a tag that can identify the sprite frame.
	private:
		
		cocos2d::Rect rect; // a rectangle used setting a sprite's texture rect.
		
		float delayUnits; // the delay units (in milliseconds) between this frame and the following frame.
		
		std::vector<OOP::Primitive *> prims;

	protected:


	} SSAnimationFrame;

	// a manager that runs the animation.
	// this works by moving around a textureRect on a sprite sheet, As such, only sprite sheets should be used.
	typedef class SpriteSheetAnimation
	{
	public:
		/*
		 * instatiates a sprite sheet animation with a sprite. Make sure to call runAnimation() to start the animation.
		 *
		 * spriteSheet: the sprite used for the animation.
		 * totalLoops: the amount of loops the animation has. Set to '0' by default.
		 * infiniteLoop: determines if the sprite infinitely loops or not. If so, 'loops' is just set to 0.
		 * delayUnits: the shared delay between all frames. This only occurs if 'sharedDelay' is true.
		 * restoreOriginalFrame: if true, restores frame 1 of the animation once all loops are finished.
		 * 
		*/
		SpriteSheetAnimation(cocos2d::Sprite * spriteSheet, unsigned int totalLoops = 0, bool infiniteLoop = false, float delayUnits = 0.0F, bool sharedDelay = true, bool restoreOriginalFrame = true);
		
		/*
		 * instatiates a sprite sheet animation with a sprite and its frames. If 'sharedDelay' is true, all sprite frames have the same amount of time between them.
		 *
		 * spriteSheet: the sprite used for the animation.
		 * frames: the animation frames for the sprite sheet.
		 * totalLoops: the amount of loops the animation has. Set to '0' by default.
		 * infiniteLoop: determines if the sprite infinitely loops or not. If so, 'loops' is just set to 0.
		 * delayUnits: the shared delay between all frames. This only occurs if 'sharedDelay' is true.
		 * restoreOriginalFrame: if true, restores frame 1 of the animation once all loops are finished.
		 *
		*/
		SpriteSheetAnimation(cocos2d::Sprite * spriteSheet, std::vector<OOP::SpriteSheetAnimationFrame *> & frames, unsigned int totalLoops = 0, bool infiniteLoop = false, float delayUnits = 0.0F, bool sharedDelay = false, bool restoreOriginalFrame = true);
		
		// gets the amount of loops an animation has.
		// Make sure to check getInfiniteLoop() to see if the animation loops infinitely. If so, getLoops() will return 0.
		unsigned int getLoops() const;
		
		// sets the amount of loops an animation has.
		// if the total amount of loops is now greater than how many loops have been done, the animation finishes on the next update loop.
		void setLoops(unsigned int totalLoops);

		// returns how many loops have been completed.
		unsigned int getFinishedLoops() const;

		// gets whether the animation loops infinitely or not.
		bool getInfiniteLoop() const;

		// toggles the infinite loop on/off.
		void setInfiniteLoop();

		// sets whether an animation loops infinitely or not.
		void setInfiniteLoop(bool infiniteLoop);
		
		// gets the shared delay units between all frames. This is only used if getSharedDelay() is true.
		float getDelayUnits() const;

		// gets the speed of the animation.
		float getSpeed() const;

		// sets the speed of the animation. If this is less than 0, then the speed is set to '1'.
		void setSpeed(float speed);
		
		// sets the opacity of the animation as a decimal percentage (cocos does it as a fraction of 255, but this function handles it based on a decimal number)
		// If given a number less than 0.0, the opacity is set to 0.0. IF given an opacity greater than 1.0 (i.e. 100%), the opacity is set to 1.0.
		// void setOpacity(float opacity);

		// returns the opacity of the whole animation out of 1.0 (i.e. 100%). If a srite frame has had its opacity changed individually, then that sprite frame's opacity should be checked instead.
		// float getOpacity();


		// flips the animation on the x-axis if a 'true' is passed.
		// unflips the animation if a 'false' is passed.
		void setFlippedAnimationX(bool flipX);

		// flips the animation on the x-axis. This uses setFlippedAnimaitonX() and makes it the opposite of getFlippedAnimationX().
		void setFlippedAnimationX();

		// checks to see if the animation is flipped on the x-axis.
		bool getFlippedAnimationX();

		// flips the animation on the y-axis if a 'true' is passed.
		// unflips the animation if a 'false' is passed.
		void setFlippedAnimationY(bool flipY);

		// flips the animation on the y-axis. This uses setFlippedAnimaitonY() and makes it the opposite of getFlippedAnimationY().
		void setFlippedAnimationY();

		// checks to see if the animation is flipped on the y-axis.
		bool getFlippedAnimationY();



		// sets the shared delay units between all frames. If you want to use the delay units in the sprite frame.
		void setDelayUnits(float & delayUnits);

		// gets whether all frames use the same amount of delay frames (true) or each have their own frame time (false).
		bool getSharedDelay() const;

		// sets whether to have each frame use the same amount of delay units (true), or have each frame use their own amount of delay units (false)
		void setSharedDelay(bool sharedDelay);
		
		// gets whether the original frame (frame 1) gets restored at the end of the animation.
		bool getRestoreOriginalFrame() const;

		// if true, the original frame (frame 1) is restored once the animation finishes.
		void setRestoreOriginalFrame(bool restoreFrame1);
	
		// returns the sprite sheet.
		cocos2d::Sprite * getSpriteSheet() const;

		// gets the current frame of animation.
		OOP::SpriteSheetAnimationFrame * getCurrentFrame() const;

		// gets the index of the current frame of animation.
		unsigned int getCurrentFrameIndex() const;

		// returns all of the frames in the sprite sheet.
		std::vector<OOP::SpriteSheetAnimationFrame * > getFrames() const;

		// sets all of the frames in the sprite sheet.
		void setFrames(std::vector<OOP::SpriteSheetAnimationFrame * > & newFrames);

		void add(OOP::SpriteSheetAnimationFrame * newFrame); // adds a frame to the end of the sprite sheet.

		void subtract(OOP::SpriteSheetAnimationFrame * newFrame); // removes a frame from the sprite sheet.

		void operator+=(OOP::SpriteSheetAnimationFrame * newFrame); // (+) operator - adds in passed object

		void operator-=(OOP::SpriteSheetAnimationFrame * newFrame); // (-) operator - removes passed object

		OOP::SpriteSheetAnimationFrame * operator[](const unsigned int index); // ([]) operator - gets platform stored at provided index


		// gets the name of the sprite sheet animation.
		std::string getName() const;
		
		 // sets the name of the sprite sheet animtion.
		void setName(std::string name);

		// gets the description of the sprite sheet animation.
		std::string getDescription() const;

		// sets the name of the sprite sheet animtion.
		void setDescription(std::string desc);

		// gets a tag representing the animation. 0 by default.
		int getTag() const;

		// sets the tag for the sprite animation.
		void setTag(int tag);


		// gets whether the animation is running or not. This will return true even if the animation is paused.
		bool isRunning();

		// starts running an animation from its beginning.
		void runAnimation();
		
		// stops an animation. This returns the animation back to its start.
		void stopAnimation();

		// pauses an animation.
		void pauseAnimation();

		// unpauses an animation.
		void unpauseAnimation();

		// an update loop that updates the animation to check for what frame it should be on. This should be provided with deltaTime.
		void update(float deltaTime);

	private:
		cocos2d::Sprite * spriteSheet; // the sprite sheet.
		std::vector<OOP::SpriteSheetAnimationFrame *> frames; // the frames of the animation.

		unsigned int totalLoops = 0; // how many times the animation loops
		unsigned int finishedLoops = 0; // the amount 
		bool infiniteLoop = true; // determines if the animation loops infinitely. If so, then 'getLoops' will be 0.
		
		

		float delayUnits = 0.0F; // the amount of delay units for all frames. This is set to 0 if each frame has its own delayUnits.
		float speed = 1.0F; // the speed of the animation. It cannot be below or equal to zero.
		bool sharedDelay = false; // deterimes whether all sprites share a delay.
		bool restoreOriginalFrame = true; // determines whether to restore the first frame of animation or not.
		bool flipX = false; // saves whether to flip the animation on the x-axis.
		bool flipY = false; // saves whether to flip the animation on the y-axis.

		std::string name = ""; // a name for the animation.
		std::string description = ""; // a description for the animation.
		int tag = 0; // a tag that can identify the animation.

		bool running = false; // sets whether the animation is running or not.
		bool paused = false; // pauses an animation if true.
		float frameTime = 0.0F; // the amount of time the frame has been on screen for. This is used to check when the frames should be switched.
		unsigned int index = 0; // the index of the current frame.

	protected:

	} SSAnimation;
}
