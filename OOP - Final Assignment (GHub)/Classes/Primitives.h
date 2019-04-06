// Used to create primitive objects; re-used lab assignment
#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include "cocos/base/ccTypes.h"
#include "cocos/math/Vec2.h"
#include "cocos/math/Vec3.h"
#include "cocos/2d/ccdrawnode.h"
#include "2d/CCDrawNode.h"

/*
// Using a namespace caused issues, so it is no longer used.
namespace cocos2d // includes specific classes from cocos2d
{
	class Vec2;
	class Vec3;
	class DrawNode;
}
*/

namespace OOP
{

	// a base primitive class. This has a 'pure virtual' function so that the users can't create a primitive without specifying what shape it is.
	// NOTE: this class originally didn't have a Primitive class, with said functions being hard coded for each derived class.
	//	- these functions have been commented out, since they are no longer needed. If these comments are still in place, then they were not removed in time.
	class Primitive
	{
	public:
		// creates the draw node
		Primitive(const short int ID);
		// releases the drawNode
		virtual ~Primitive();

		// returns square primitive
		cocos2d::DrawNode * getPrimitive() const;

		// gets the position of the vector.
		cocos2d::Vec2 getPosition() const;

		// sets the position of the primitive. This is a 'pure virtual' function so that an object of this type can't be created.
		// the setPosition() was made virtual because some other things may need to be repositioned in specific primitives.
		virtual void setPosition(cocos2d::Vec2 position) = 0;

		// returns whether the collision shape is visible or not.
		bool isVisible() const; 

		// turns on/off the visibility of the primitive.
		void setVisible(bool visible);

		// toggle for visible; it turns it on/off.
		void setVisible();

		// gets the tag of the primitive.
		int getTag() const;

		// sets the tag of the primitive. This is 0 by default.
		void setTag(int tag);
			
		// if 'true', then that means this shape is being used for collisions. If false, then this shape is NOT being used for collisions.
		// Note that this parameter is essentially meaningless for grid and line primitives.
		// primitives will have have their opacity cut by 50% when they are not active.
		// this is true by default.
		bool isActive() const;
			
		// sets whether a primitive is active or not, i.e. if it's open for collisions or not.
		// Note that this parameter is essentially meaningless for grid and line primitives.
		// primitives will have have their opacity cut by 50% when they are not active.
		void setActive(bool active);

		// toggle's primitive functionality as a collision shape on and off.
		// Note that this parameter is essentially meaningless for grid and line primitives.
		// primitives will have have their opacity cut put at 50% when they are not active.
		void setActive();

		/*
			* The type of the primitive. Use this for reference when you need to know what to downcast to.
			* 1 = sqaure (AABB)
			* 2 = square (OBB)
			* 3 = circle
			* 4 = line
			* 5 = capsule
			* 6 = grid

			// returns an id that identifies what type the primitive is.
		*/
		short int getId();

		/*
		* collision between two primitives. Returns false if there is no check availble, at least one of the primitives is inactive, or if there is no collision.
		* These are the accurate collision checks that have proper algorithms. 
			* AABB - AABB
			* Circle - Circle
			* AABB - OBB
		
		* These are the 'inaccurate' collision checks. NONE OF THESE HAVE BEEN IMPLEMENTED.
			* Capsule - Capsule (this cannot do OBB and Circle, so the circles are made into AABBs for the sake of the check)
			* OBB - Circle (this makes the circle an AABB box in order for it to work).
		*/
		static bool collision(OOP::Primitive * p1, OOP::Primitive * p2);

	private:
		int tag = 0; // an identification tag

		bool active = true; // used so that this collision shape can be turned on and off.

	protected:
		cocos2d::DrawNode * m_Node; // drawNode member

		/*
		 * The type of the primitive. Use this for reference when you need to know what to downcast to.
		 * 1 = sqaure (AABB)
		 * 2 = square (OBB)
		 * 3 = circle
		 * 4 = line
		 * 5 = capsule
		 * 6 = grid

		 // an 'ID' used to determine what type a primitive is. This can't be const because PrimitiveOrientedSquare has a different ID than PrimitiveSquare, and cannot set this variable it it's const.
		*/
		short int ID = 0;
	};

	class PrimitiveSquare : public Primitive // square
	{
	public:
		// creates and initalizes drawNode for square.
		PrimitiveSquare(const cocos2d::Vec2 &a_StartPosition, const cocos2d::Vec2 &a_EndPosition, const cocos2d::Color4F colour = cocos2d::Color4F::RED);

		// creates a square draw primitive. This is based on the middle of the rect.
		PrimitiveSquare(const cocos2d::Vec2 position, const float width, const float height, const cocos2d::Color4F colour = cocos2d::Color4F::RED);

		// creates a square draw primitive. This reuses the constructor with the (cocos2d::vec2, float, float) parameter, but has the two floats be guaranteed to be the same value.
		// This is based on the middle of the square.
		PrimitiveSquare(const cocos2d::Vec2 position, const float sideLength, const cocos2d::Color4F colour = cocos2d::Color4F::RED);

		// destructor is called when an object of type PrimitiveSquare is destroyed.
		~PrimitiveSquare();

		// returns square primitive
		cocos2d::DrawNode * getPrimitive() const;

		// sets the position of the primitive.
		void setPosition(cocos2d::Vec2 position);

		// returns a rect representing the primitive.
		// If it's an oriented primitive square, then it will return a rectangle representing the primitive at a rotation factor of 0.0F.
		cocos2d::Rect getRect() const;

		// the width of the rectangle primitive.
		const float m_WIDTH;
		
		// the height of the rectangle primitive.
		const float m_HEIGHT;

	private:

	};

	// a child of the PrimitiveSquare class that allows for rotations.
	class PrimitiveOrientedSquare : public PrimitiveSquare
	{
	public:
		// creates and initalizes drawNode for an oriented square
		PrimitiveOrientedSquare(const cocos2d::Vec2 &a_StartPosition, const cocos2d::Vec2 &a_EndPosition, float rotation = 0.0F, bool inDegrees = false, const cocos2d::Color4F colour = cocos2d::Color4F::RED);

		// creates an oriented square draw primitive. This is based on the middle of the rect.
		PrimitiveOrientedSquare(const cocos2d::Vec2 & position, const float & width, const float & height, float rotation = 0.0F, bool inDegrees = false, const cocos2d::Color4F colour = cocos2d::Color4F::RED);

		// turns a primitive square into an orented primitive square with a rotation factor of 0.
		PrimitiveOrientedSquare(const OOP::PrimitiveSquare &);

		// returns the rotation factor of the primitive in degrees.
		float getRotationInDegrees() const;

		// sets the rotation factor of the primitive in degrees.
		void setRotationInDegrees(float rotation);

		// returns the rotation factor of the primitive in radians.
		float getRotationInRadians() const;

		// sets the rotation factor of the primitive in radians.
		void setRotationInRadians(float rotation);
		
	private:
		
	};

	// Primitive Circle Class
	class PrimitiveCircle : public Primitive
	{
	public:
		// creates and initalizes drawNode
		PrimitiveCircle(cocos2d::Vec2 location, float radius, const cocos2d::Color4F colour = cocos2d::Color4F::RED);

		// destructor for primitive circle
		~PrimitiveCircle();

		// sets the position of the primitive.
		void setPosition(cocos2d::Vec2 position);

		// the radius of the circle.
		const float m_RADIUS = 0.0F;

	private:

	};

	// Line Primitive Class
	class PrimitiveLine : public Primitive
	{
	public:
		// creates a line draw primitive
		PrimitiveLine(cocos2d::Vec2 startingPoint, cocos2d::Vec2 endingPoint, const cocos2d::Color4F colour = cocos2d::Color4F::RED);
		
		// destructor
		~PrimitiveLine();

		// sets the position of the primitive.
		void setPosition(cocos2d::Vec2 position);

		// returns the rotation factor of the primitive in degrees.
		float getRotationInDegrees() const;

		// sets the rotation factor of the primitive in degrees.
		void setRotationInDegrees(float rotation);

		// returns the rotation factor of the primitive in radians.
		float getRotationInRadians() const;

		// sets the rotation factor of the primitive in radians.
		void setRotationInRadians(float rotation);

		// the slope of the line.
		const cocos2d::Vec2 m_DISTANCE;

		// the length of the line.
		const float m_LENGTH;
	private:

	};

	// Capsule Primitive Class
	class PrimitiveCapsule : public Primitive
	{
	public:
		// creates a capsule. The start and end points are where the circles are drawn.
		PrimitiveCapsule(cocos2d::Vec2 start, cocos2d::Vec2 end, float radius, const cocos2d::Color4F colour = cocos2d::Color4F::MAGENTA);

		// creates a capsule. The endingPoints of the capsule are based on the position provided (which is treated as the centre of the capsule), and the length given (which is the total length of the capsule).
		// the angle determines the rotation of the capsule, and is in DEGREES. The capsule is drawn 'horizontally', and must be rotated by 90 degrees to make it vertical.
		PrimitiveCapsule(cocos2d::Vec2 position, float length, float radius, const float angle, const cocos2d::Color4F colour = cocos2d::Color4F::MAGENTA);

		// destructor for capsules
		~PrimitiveCapsule();

		// sets the position of the primitive.
		void setPosition(cocos2d::Vec2 position);

		// gets the position of the circle at one of the endings of the capsule. This should be at the beginning of the capsule.
		cocos2d::Vec2 getCirclePosition1() const;

		// gets circle 1 as a circle primitive.
		OOP::PrimitiveCircle * getCircle1() const;

		// gets the position of the circle at one of the endings of the capsule. This should be at the ending of the capsule.
		cocos2d::Vec2 getCirclePosition2() const;

		// gets circle 2 as a circle primitive.
		OOP::PrimitiveCircle * getCircle2() const;

		// gets the rectangle for the capsule as an oriented square.
		OOP::PrimitiveOrientedSquare * getOrientedRect() const;

		// returns the rotation factor of the primitive in degrees.
		float getRotationInDegrees() const;

		// Keep in mind that the capsule is drawn rotated, so the rotation factor of the drawingNode is NOT the same as that the capsule.
		// e.g. if the capsule was drawn at a 30 degree angle, the drawNode is still at an angle of 0.0 degrees.
		// sets the rotation factor of the primitive in degrees.
		void setRotationInDegrees(float newTheta);

		// returns the rotation factor of the primitive in radians.
		float getRotationInRadians() const;

		// Keep in mind that the capsule is drawn rotated, so the rotation factor of the drawingNode is NOT the same as that the capsule.
		// e.g. if the capsule was drawn at a 0.8 radian angle, the drawNode is still at an angle of 0.0 radians.
		// sets the rotation factor of the primitive in radians.
		void setRotationInRadians(float newTheta);

		// the radius of the capsule.
		const float m_RADIUS;

		const float m_RECT_WIDTH; // the width (i.e. x-length) of the capsule rectangle. This is unrotated.
		const float m_RECT_HEIGHT; // the height (i.e. y-length) of the capsule rectangle This is unrotated.

	private:

		cocos2d::Vec2 m_Circle1; // saves the position of the starting circle of the capsule.

		cocos2d::Vec2 m_Circle2; // saves the position of the ending circle of the capsule.

		float m_theta; // the rotation factor of the capsule (in degrees)
	};

	// creates a grid of lines; not from original assignment
	class PrimitiveGrid : public Primitive
	{
	public:
		/*
		 * Creates a grid. Lines will keep being drawn until they exceed the bounds of the starting point and ending point.
		 *
		 * startingPoint: the starting corner of the grid.
		 * endingPoint: the ending corner of the grid.
		 * squareSize: the size of the grid spaces  (in pixels). It's the standard tile size (128.0F) by default.
		 * colour: the colour of the grid; black by default.
		 * gridBox: determines whether all the grid lines are put within a box. True by default.
		*/
		PrimitiveGrid(cocos2d::Vec2 startingPoint, cocos2d::Vec2 endingPoint, const float squareSize = 128.0F, const cocos2d::Color4F colour = cocos2d::Color4F::BLACK, const bool gridBox = true);

		/*
		 * Creates a grid. Lines will keep being drawn until they exceed the bounds of the starting point and ending point.
		 *
		 * position: the position of the grid. It is the MIDDLE of the grid.
		 * size: the size of the grid overal
		 * squareSize: the size of the grid spaces (in pixels). It's the standard tile size (128.0F) by default.
		 * colour: the colour of the grid; black by default.
		 * gridBox: determines whether all the grid lines are put within a box. True by default.
		*/
		PrimitiveGrid(cocos2d::Vec2 position, cocos2d::Size size, const float squareSize = 128.0F, const cocos2d::Color4F colour = cocos2d::Color4F::BLACK, const bool gridBox = true);

		~PrimitiveGrid();

		// sets the position of the primitive.
		void setPosition(cocos2d::Vec2 position);

		// the width of the grid. This is based on the passed parameters, and not the farthest left line and farthest right line.  As such, it assumes that all grid spaces are of equal size.
		float m_WIDTH;
		// the height of the grid. This is based on the passed parameters, and not the highest and lowest line. As such, it assumes that all grid spaces are of equal size.
		float m_HEIGHT;

		// stores the unit size (i.e. square size) of the grid.
		float m_SQUARE_SIZE; 

	private:

	};
}

#endif //!PRIMITIVES_H