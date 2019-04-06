
// Question 1: Primitive.h Creation
// #include "2d/CCDrawNode.h"
// #include "math/Mat4.h"
#include "Primitives.h"
#include "Utilities.h"
#include <iostream>



///// GENERAL PRIMITIVE //////////////////////////////////////////////////////////////////////////
OOP::Primitive::Primitive(const short int ID) : m_Node(cocos2d::DrawNode::create()), ID(ID)
{ 
	m_Node->setGlobalZOrder(10.1F); // since primitives are treated as collision shapes, they have the global z order of  10.1F.
	m_Node->setVisible(false); // hides the draw node from view.
}

// releases the drawNode. This was originally done in every destructor, but now only happens here.
OOP::Primitive::~Primitive() { /*m_Node->release();*/ m_Node->removeFromParent(); }

// returns the primitive.
cocos2d::DrawNode * OOP::Primitive::getPrimitive() const { return m_Node; }

// gets the position of the drawNode.
cocos2d::Vec2 OOP::Primitive::getPosition() const { return m_Node->getPosition(); }

// gets the visibility of the m_Node
bool OOP::Primitive::isVisible() const { return m_Node->isVisible(); }

// sets the visibility of the collision shape.
void OOP::Primitive::setVisible(bool visible) { m_Node->setVisible(visible); }

// toggles the visibility of the collision shape.
void OOP::Primitive::setVisible() { setVisible(!m_Node->isVisible()); }

// gets the tag for the primitive.
int OOP::Primitive::getTag() const { return tag; }

// sets the tag of the primitive.
void OOP::Primitive::setTag(int tag) { this->tag = tag; }

// if true, the primitive is active or collisions. If false, it is not active for collisions.
// this does not apply to lines and grid primitives.
bool OOP::Primitive::isActive() const { return active; }

// sets whether a primitive is available for collisions or not.
// primitives that are not available for collisions have their opacity brought down to 50%.
// this parameter is basically worthless for lines and grids.
void OOP::Primitive::setActive(bool active)
{
	// if the primitive activity is being turned on, then opacity is set for 100%. Opacity is out of 255.
	(active) ? m_Node->setOpacity(255.0F) : m_Node->setOpacity(127.5);

	this->active = active;
}

// toggle's the primitive's availibility for collisions on and off.
// Note that this parameter is essentially meaningless for grid and line primitives.
// primitives will have have their opacity cut put at 50% when they are not active.
void OOP::Primitive::setActive() { setActive(!active); }

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
short int OOP::Primitive::getId() { return ID; }

// collision between two active primitives.
bool OOP::Primitive::collision(OOP::Primitive * p1, OOP::Primitive * p2)
{
	bool col = false;

	if (p1 == nullptr || p2 == nullptr) // returns false of one of these are null.
		return false;

	if (!p1->isActive() || !p2->isActive()) // returns false if one of these are inactive.
		return false;

	if (p1->getId() == 1 && p2->getId() == 1) // AABB and AABB
	{
		return umath::aabbCollision(&(((OOP::PrimitiveSquare *)p1)->getRect()), &(((OOP::PrimitiveSquare *)p2)->getRect()));
	}
	else if (p1->getId() == 2 && p2->getId() == 2) // OBB-OBB
	{
		return umath::obbCollision(((OOP::PrimitiveOrientedSquare *)p1)->getRect(), ((OOP::PrimitiveOrientedSquare *)p1)->getRotationInRadians(),
								  ((OOP::PrimitiveOrientedSquare *)p2)->getRect(), ((OOP::PrimitiveOrientedSquare *)p2)->getRotationInRadians(),
								  false);
	}
	else if (p1->getId() == 3 && p2->getId() == 3) // circle-circle
	{
		return umath::circleCollision(p1->getPosition(), ((OOP::PrimitiveCircle *)p1)->m_RADIUS, p2->getPosition(), ((OOP::PrimitiveCircle *)p2)->m_RADIUS);
	}
	else if (p1->getId() == 5 && p2->getId() == 5) // capsule-capsule
	{

		// Proper checks
		col = collision(((OOP::PrimitiveCapsule *)p1)->getCircle1(), ((OOP::PrimitiveCapsule *)p2)->getCircle1()); // p1 circ1 and p2 circ1
		if (col == true)
			return col;

		col = collision(((OOP::PrimitiveCapsule *)p1)->getCircle1(), ((OOP::PrimitiveCapsule *)p2)->getCircle2());// p1 circ1 and p2 circ2
		if (col == true)
			return col;

		col = collision(((OOP::PrimitiveCapsule *)p1)->getCircle2(), ((OOP::PrimitiveCapsule *)p2)->getCircle1()); // p1 circ2 and p2 circ1
		if (col == true)
			return col;

		col = collision(((OOP::PrimitiveCapsule *)p1)->getCircle2(), ((OOP::PrimitiveCapsule *)p2)->getCircle2());// p1 circ2 and p2 circ2
		if (col == true)
			return col;

		col = collision(((OOP::PrimitiveCapsule *)p1)->getOrientedRect(), ((OOP::PrimitiveCapsule *)p2)->getOrientedRect()); // p1 oriented rect and p2 oriented rect

		// Improper checks
		// col = collision(((OOP::PrimitiveCapsule *)p1)->getOrientedRect(), OOP::PrimitiveSquare(p2->getPosition(), p2->)
	}
	else if ((p1->getId() == 1 && p2->getId() == 2) || (p1->getId() == 2 || p2->getId() == 1)) // AABB and OBB (or OBB and AABB)
	{
		if (p1->getId() == 2 || p2->getId() == 1) // flips the two primitives aorund so that the collision check can be done.
			return collision(p2, p1);

		return umath::obbCollision(((OOP::PrimitiveSquare *)p1)->getRect(), 0.0F, ((OOP::PrimitiveOrientedSquare *)p2)->getRect(), ((OOP::PrimitiveOrientedSquare *)p2)->getRotationInRadians(), false);
	}
	else if ((p1->getId() == 1 && p2->getId() == 3) || (p1->getId() == 3 || p2->getId() == 1)) // AABB and circle
	{
		if (p1->getId() == 3 || p2->getId() == 1) // flips the two shapes around so that they acn use this check
			return collision(p2, p1);

		return umath::aabbCircleCollision(((OOP::PrimitiveSquare *)p1)->getRect(), p2->getPosition(), ((OOP::PrimitiveCircle *)p2)->m_RADIUS);

	}

	return false;
}



///// SQUARE /////////////////////////////////////////////////////////////////////////////
// Question 3: initalization of the DrawNode (Square)
OOP::PrimitiveSquare::PrimitiveSquare(const cocos2d::Vec2 &a_StartPosition, const cocos2d::Vec2 &a_EndPosition, const cocos2d::Color4F colour) 
	: Primitive(1), /*m_Node(cocos2d::DrawNode::create()),*/ m_WIDTH(abs((a_EndPosition - a_StartPosition).x)), m_HEIGHT(abs((a_EndPosition - a_StartPosition).y))
{
	// draws the rectangle
	m_Node->drawRect(cocos2d::Vec2(0.0F, 0.0F) - cocos2d::Vec2(m_WIDTH / 2, m_HEIGHT / 2), cocos2d::Vec2(0.0F, 0.0F) + cocos2d::Vec2(m_WIDTH / 2, m_HEIGHT / 2), colour);
	m_Node->setPosition((a_StartPosition + a_EndPosition) / 2); // sets the position to be the middle of the two corners of the quadrilateral.

	//m_Node->setAnchorPoint(cocos2d::Vec2(0.5F, 0.5F));
	//m_Node->drawRect(a_StartPosition, a_EndPosition, colour);
	//m_Position = a_StartPosition + (a_EndPosition - a_StartPosition) / 2; // gets the location of the primitive.
}

// creates a rect based on a position, length, and width provided by the user. This is based on the middle of the rect.
OOP::PrimitiveSquare::PrimitiveSquare(const cocos2d::Vec2 position, const float width, const float height, const cocos2d::Color4F colour)
	: Primitive(1), /*m_Node(cocos2d::DrawNode::create()),*/ m_WIDTH(width), m_HEIGHT(height)
{
	// draws the rectangle at location (0, 0).
	m_Node->drawRect(cocos2d::Vec2(0.0F, 0.0F) - cocos2d::Vec2(width / 2, height / 2), cocos2d::Vec2(0.0F, 0.0F) + cocos2d::Vec2(width / 2, height / 2), colour);
	m_Node->setPosition(position); // sets the position of the node to be where the rectangle should be.

	// m_Node->drawRect(cocos2d::Vec2(position.x - width / 2, position.y - height / 2), cocos2d::Vec2(position.x + width / 2, position.y + height / 2), colour);
	// m_Position = position; // saves the location of the square.
}

// creates a rect based on a given position and side length; this is guaranteed to be a square. This is based on the middle of the square.
OOP::PrimitiveSquare::PrimitiveSquare(const cocos2d::Vec2 position, const float sideLength, const cocos2d::Color4F colour) : PrimitiveSquare(position, sideLength, sideLength, colour) {}

// called when deleting the square. The release of the node now happens in the base class.
OOP::PrimitiveSquare::~PrimitiveSquare() { /*m_Node->release();*/ }

// Question 4: returns the square primitive
cocos2d::DrawNode * OOP::PrimitiveSquare::getPrimitive() const { return m_Node; }

// sets the position of the primitive.
void OOP::PrimitiveSquare::setPosition(cocos2d::Vec2 position)
{
	m_Node->setPosition(position); // changes the node's position.

	/*
	// because the position of the node isn't the same as the primitive itself, this calculation is needed.
	// m_Node->setPosition(m_Node->getPosition() - this->m_Position - position);
	if (m_Node == nullptr)
		std::cout << "What?" << std::endl;

	// because the position of the node isn't the same as the primitive itself, this calculation is needed.
	m_Node->setPosition(m_Node->getPosition() + position - m_Position);
	m_Position = position;
	*/
}

// returns the rectangle object representing the primitive graphic.
cocos2d::Rect OOP::PrimitiveSquare::getRect() const { return cocos2d::Rect(m_Node->getPositionX() - m_WIDTH / 2, m_Node->getPositionY() - m_HEIGHT / 2, m_WIDTH, m_HEIGHT); }

///// ORIENTED SQUARE ////////////////////////////////////////////////////////////////////
// bases on start and end position. This reuses a different function.
OOP::PrimitiveOrientedSquare::PrimitiveOrientedSquare(const cocos2d::Vec2 & a_StartPosition, const cocos2d::Vec2 & a_EndPosition, float rotation, bool inDegrees, const cocos2d::Color4F colour)
	: PrimitiveOrientedSquare((a_StartPosition + a_EndPosition) / 2.0F, abs((a_EndPosition - a_StartPosition).x), abs((a_EndPosition - a_StartPosition).y), rotation, inDegrees, colour) {}

OOP::PrimitiveOrientedSquare::PrimitiveOrientedSquare(const cocos2d::Vec2 & position, const float & width, const float & height, float rotation, bool inDegrees, const cocos2d::Color4F colour)
	: PrimitiveSquare(position, width, height, colour)
{
	ID = 2; // sets the ID for the oriented square.

	if (inDegrees == false) // if the angle is in radians, it is converted into degrees.
		rotation = umath::radiansToDegrees(rotation);

	m_Node->setRotation(rotation); // rotates the drawNode.
}

// creates a primitive oriented square out of a regular primitive square.
OOP::PrimitiveOrientedSquare::PrimitiveOrientedSquare(const OOP::PrimitiveSquare & sqrPrim)
	: PrimitiveSquare(sqrPrim)
{
	ID = 2;
	m_Node->setRotation(0.0F);
}

// gets the rotation factor in degrees. This is inherently how the rotation factor is stored.
float OOP::PrimitiveOrientedSquare::getRotationInDegrees() const { return m_Node->getRotation(); }

// sets the rotation factor of the primitive using degrees. // sets the rotation factor for the primitive. 
void OOP::PrimitiveOrientedSquare::setRotationInDegrees(float rotation)  { m_Node->setRotation(rotation); }

// gets rthe rotation of the primitive in radians
float OOP::PrimitiveOrientedSquare::getRotationInRadians() const { return umath::degreesToRadians(m_Node->getRotation()); }

// sets the rotation of the primitive in radians
void OOP::PrimitiveOrientedSquare::setRotationInRadians(float rotation) { m_Node->setRotation(umath::radiansToDegrees(rotation)); }

///// CIRCLE /////////////////////////////////////////////////////////////////////////////
// initalizes the drawNode
OOP::PrimitiveCircle::PrimitiveCircle(cocos2d::Vec2 location, float radius, const cocos2d::Color4F colour) : Primitive(3), /*m_Node(cocos2d::DrawNode::create()),*/ m_RADIUS(abs(radius))
{
	m_Node->drawCircle(cocos2d::Vec2(0.0F, 0.0F), abs(radius), 20.0F, 30, false, cocos2d::Color4F(0.0, 0.0F, 1.0F, 1.0F)); // draws the circle at location (0, 0).
	m_Node->setPosition(location); // moves the circle to where it shoudld be.
	// m_Node->drawCircle(location, abs(radius), 20.0F, 30, false, cocos2d::Color4F(0.0, 0.0F, 1.0F, 1.0F));
	// m_Position = location;
}

OOP::PrimitiveCircle::~PrimitiveCircle() { /*m_Node->release();*/ }

// sets the position of the primitive.
void OOP::PrimitiveCircle::setPosition(cocos2d::Vec2 position)
{
	m_Node->setPosition(position); // changes the position of the draw node.
	// because the position of the node isn't the same as the primitive itself, this calculation is needed.
	// m_Node->setPosition(m_Node->getPosition() + position - m_Position);
	//this->m_Position = position;
}


///// LINE ///////////////////////////////////////////////////////////////////////////////
// initalization of the DrawNode (Line)
OOP::PrimitiveLine::PrimitiveLine(cocos2d::Vec2 startingPoint, cocos2d::Vec2 endingPoint, const cocos2d::Color4F colour)
	: Primitive(4), /*m_Node(cocos2d::DrawNode::create()),*/ m_DISTANCE(cocos2d::Vec2(endingPoint - startingPoint)),
	m_LENGTH (sqrt(pow((endingPoint - startingPoint).x, 2) + pow((endingPoint - startingPoint).y, 2)))
{
	// draws the line with its centre at position (0.0F, 0.0F).
	m_Node->drawLine(cocos2d::Vec2(0.0F - abs(m_DISTANCE.x / 2), 0.0F - abs(m_DISTANCE.y / 2)), cocos2d::Vec2(0.0F + abs(m_DISTANCE.x / 2), 0.0F + abs(m_DISTANCE.y / 2)), colour);
	m_Node->setPosition((startingPoint + endingPoint) / 2); // sets the position of the node to where the shape should be.

	// m_Node->drawLine(startingPoint, endingPoint, colour); // creating the line
	// m_Position = startingPoint + (endingPoint - startingPoint) / 2; // gets the location of the primitive.
}


OOP::PrimitiveLine::~PrimitiveLine() { /*m_Node->release();*/ }

// sets the position of the primitive.
void OOP::PrimitiveLine::setPosition(cocos2d::Vec2 position)
{
	m_Node->setPosition(position); // sets the position of the node.

	// because the position of the node isn't the same as the primitive itself, this calculation is needed.
	// m_Node->setPosition(m_Node->getPosition() + position - m_Position);
	// this->m_Position = position;
}

// gets the rotation factor in degrees. This is inherently how the rotation factor is stored.
float OOP::PrimitiveLine::getRotationInDegrees() const { return m_Node->getRotation(); }

// sets the rotation factor of the primitive using degrees. // sets the rotation factor for the primitive. 
void OOP::PrimitiveLine::setRotationInDegrees(float rotation) { m_Node->setRotation(rotation); }

// gets rthe rotation of the primitive in radians
float OOP::PrimitiveLine::getRotationInRadians() const { return umath::degreesToRadians(m_Node->getRotation()); }

// sets the rotation of the primitive in radians
void OOP::PrimitiveLine::setRotationInRadians(float rotation) { m_Node->setRotation(umath::radiansToDegrees(rotation)); }

//// CAPSULE /////////////////////////////////////////////////////////////////////////////
// creates a capsule
OOP::PrimitiveCapsule::PrimitiveCapsule(cocos2d::Vec2 startingPoint, cocos2d::Vec2 endingPoint, float radius, const cocos2d::Color4F colour)
	: Primitive(5), /*m_Node(cocos2d::DrawNode::create()),*/ m_RADIUS(abs(radius)), m_RECT_WIDTH(abs(endingPoint.x - startingPoint.x)), m_RECT_HEIGHT(abs(endingPoint.y - startingPoint.y))
{
	// Works when angle is greater than 3.14 rad, or when a 90 degree angle

	// The 'triangle' variable is used to save the three sides of a triangle that represents the distance between the starting point and ending point.
	/*
		* x: the 'x' distance between the two points. This is the base of the triangle.
		* y: the 'y' distance between the two points. This is the height of the traingle.
		* z: the distance between the starting point and ending point. This is the hypotenuse of the triangle.
	*/
	cocos2d::Vec2 position; // saves where the capsule should be drawn. Remove this if you want to go back to the way it was before.
	cocos2d::Vec3 triangle;

	float angle = 0.0F; // the angle of rotation used on the lines.
	cocos2d::Vec2 offset(0, radius); // used to offset the location of the lines. By default, lines are connected to the centres of the two circles.
	cocos2d::Vec2 tempVec; // a temporary vector used for swapping values.
	
	radius = abs(radius); // making the radius positive.

	// if the ending point is below te starting point, they're swapped so the calculation works.
	if (endingPoint.x < startingPoint.x)
	{
		tempVec = endingPoint;
		endingPoint = startingPoint;
		startingPoint = tempVec;
	}

	position = (startingPoint + endingPoint) / 2; // gets the position of the capsule.

	// gets the difference between the two points, i.e. an x distance and y distance. This results in a vector, and is used to form the triangle.
	triangle = cocos2d::Vec3(endingPoint.x - startingPoint.x, endingPoint.y - startingPoint.y, 0); // gets the base and height of the triangle.

	// gets the distance between the points via the Pythagorean theorem. This is saved as the 'z' value of the triangle (Vec3) variable.
	triangle.z = sqrt(pow(triangle.x, 2) + pow(triangle.y, 2));

	// uses trigonemtry (sine (SOH), cosine (CAH) and tangent (TOA)) to get the angle between the two circles, based on their centre points.
	angle = asinf(triangle.y / triangle.z); // gets the angle of the triangle

	// rotates the coordinate points using a rotation matrix. Well, it technically ISN'T using a matrix, but it's modeled after a rotation matirx.
	// This uses a rotation matrix setup, which is modeled below. With matricies, the calculation would be done in the way shown below, which is what was implemented.
	// [ cos a , -sin a] [x] = [ xcos a - ysin a ]
	// [ sin a ,  cos a] [y] = [ xsin a + ycos a ]

	// angle = M_PI - angle; // flips the angle to the adjacent quadrant. Used to move the centre lines.
	offset = cocos2d::Vec2(offset.x * (cosf(angle)) - offset.y * (sinf(angle)), offset.x * (sinf(angle)) + offset.y * (cosf(angle)));
	
	/*
	// revised version. This is meant to draw an axis-aligned capsule that then gets rotated to where it should be. It doesn't work...
	m_Node->drawCircle(cocos2d::Vec2((startingPoint - position).x, 0.0F), radius, 0.0F, 30, false, colour);
	m_Node->drawCircle(cocos2d::Vec2((endingPoint - position).x, 0.0F), radius, 0.0F, 30, false, colour);

	m_Node->drawLine(startingPoint + offset - position, cocos2d::Vec2((endingPoint + offset - position).x, (startingPoint + offset - position).y), colour);
	m_Node->drawLine(startingPoint - offset - position, cocos2d::Vec2((endingPoint - offset - position).x, (startingPoint - offset - position).y), colour);
	*/

	// original drawLines
	// drawing the starting and ending circles. These now subtract the position of the capsule so that the centre is at (0, 0).
	m_Node->drawCircle(startingPoint - position, radius, 0.0F, 30, false, colour);
	m_Node->drawCircle(endingPoint - position, radius, 0.0F, 30, false, colour);

	// drawing the two lines.  These now subtract the position of the capsule so that the centre is at (0, 0).
	m_Node->drawLine(startingPoint + offset - position, endingPoint + offset - position, colour);
	m_Node->drawLine(startingPoint - offset - position, endingPoint - offset - position, colour);

	m_Node->setPosition(position); // sets the position of the drawNode to where the capsule should be.
	// m_Node->setRotation(m_theta);
	m_Circle1 = startingPoint; // saves the location of the starting point as the location of the first circle.
	m_Circle2 = endingPoint; // saves the location of the ending circle as the endingPoint of the capsule, which is where the circle was drawn.

	// m_Position = startingPoint + (endingPoint - startingPoint) / 2; // saves the location of the primitive.
	m_theta = angle; // saves the angle in degrees
}

// creates a capsule. The endingPoints of the capsule are based on the position provided (which is treated as the centre of the capsule), and the length given (which is the total length of the capsule).
		// the angle determines the rotation of the capsule, and is in DEGREES. The capsule is drawn 'horizontally', and must be rotated by 90 degrees to make it vertical.
OOP::PrimitiveCapsule::PrimitiveCapsule(cocos2d::Vec2 position, float length, float radius, const float angle, const cocos2d::Color4F colour)
	: PrimitiveCapsule(
		position - umath::rotate(cocos2d::Vec2(abs(length) / 2 - abs(radius), 0.0F), angle, true), 
		position + umath::rotate(cocos2d::Vec2(abs(length) / 2 - abs(radius), 0.0F), angle, true),
		radius, colour)
{
	// the code below is a more readiable way of how the calculation works.
	/*
	cocos2d::Vec2 capPos = position; // saves the position of the capsule.

	cocos2d::Vec2 startingPos{ capPos.x - (abs(length) - abs(radius)) / 2, capPos.y }; // calculates the starting position (i.e. the location of the first circle).
	cocos2d::Vec2 endingPos{ capPos.x + (abs(length) - abs(radius)) / 2, capPos.y }; // calculates the ending position (i.e. the location of the second circle).

	startingPos -= capPos; // moves the starting position (i.e. position of circle 1) so that it's proportional to the origin of the drawNode (0.0F, 0.0F).
	endingPos -= capPos; // moves the ending position (i.e. position of circle 2) so that it's proportional to the origin of the drawNode (0.0F, 0.0F).

	startingPos = umath::rotate(startingPos, angle); // rotates the startingPosition
	endingPos = umath::rotate(endingPos, angle); // rotates the endingPosition

	startingPos += capPos; // moves the capsule to where it should be.
	endingPos += capPos; // moves the capsule to where it should be.
	*/
}

// destructor for a capsule
OOP::PrimitiveCapsule::~PrimitiveCapsule() { /*m_Node->release();*/ }

// sets the position of the primitive.
void OOP::PrimitiveCapsule::setPosition(cocos2d::Vec2 position)
{
	cocos2d::Vec2 oldPos = m_Node->getPosition(); // gets the old position of the capsule.

	m_Node->setPosition(position);
	m_Circle1 += position - oldPos; // gets the location of the new circle by offsetting it by how much the capsule moved.
	m_Circle2 += position - oldPos; // gets the location of the new circle by offsetting it by how much the capsule moved.

	/*
	// because the position of the node isn't the same as the primitive itself, this calculation is needed.
	m_Node->setPosition(m_Node->getPosition() + position - m_Position);
	
	// changes the positions of the circles
	m_Circle1 += position - m_Position;
	m_Circle2 += position - m_Position;

	this->m_Position = position;
	*/
}

// gets the starting circle of the capsule
cocos2d::Vec2 OOP::PrimitiveCapsule::getCirclePosition1() const { return m_Circle1; }

// gets the first circle as a primitive.
OOP::PrimitiveCircle * OOP::PrimitiveCapsule::getCircle1() const { return new OOP::PrimitiveCircle(m_Circle1, m_RADIUS); }

// gets the ending circle of the capsule
cocos2d::Vec2 OOP::PrimitiveCapsule::getCirclePosition2() const { return m_Circle2; }

// gets circle 2 as a primitive.
OOP::PrimitiveCircle * OOP::PrimitiveCapsule::getCircle2() const { return new OOP::PrimitiveCircle(m_Circle2, m_RADIUS); }

// gets an oriented rectangle from the capsule.
OOP::PrimitiveOrientedSquare * OOP::PrimitiveCapsule::getOrientedRect() const { return new OOP::PrimitiveOrientedSquare(getPosition(), m_RECT_WIDTH, m_RECT_HEIGHT); }

// gets the rotation factor of the capsule in degrees.
float OOP::PrimitiveCapsule::getRotationInDegrees() const { return m_theta; }

// sets the rotation factor of the capsule.
void OOP::PrimitiveCapsule::setRotationInDegrees(float newTheta)
{
	float nodeTheta = m_Node->getRotation(); // gets the rotation factor of the drawNode (in degrees).
	float netTheta = newTheta - m_theta; // gets the net change in the capsule's rotation factor.

	m_Node->setRotation(m_Node->getRotation() + netTheta); // sets the node's rotation based on what the orientation of the capsule should be.
	m_theta = newTheta; // saves the rotation factor of the capsule.
}

// gets the rotation factor in radians
float OOP::PrimitiveCapsule::getRotationInRadians() const { return umath::degreesToRadians(m_Node->getRotation()); }

// sets the rotation factor in radians
void OOP::PrimitiveCapsule::setRotationInRadians(float newTheta){ setRotationInDegrees(umath::radiansToDegrees(newTheta)); }

///// GRID ///////////////////////////////////////////////////////////////////////////////
// creates a grid
OOP::PrimitiveGrid::PrimitiveGrid(cocos2d::Vec2 startingPoint, cocos2d::Vec2 endingPoint, const float squareSize, const cocos2d::Color4F colour, const bool gridBox)
	: Primitive(6), /*m_Node(cocos2d::DrawNode::create()),*/ m_WIDTH(abs((startingPoint - endingPoint).x)), m_HEIGHT(abs((startingPoint - endingPoint).y)), m_SQUARE_SIZE(squareSize)
{
	const cocos2d::Vec2 POSITION = (startingPoint + endingPoint) / 2; // gets the position of the grid.
	cocos2d::Vec2 tempVec1;
	cocos2d::Vec2 tempVec2;

	if (startingPoint.x > endingPoint.x) // switches the start point and end point if the ending point is before the starting point.
	{
		tempVec1 = startingPoint;
		startingPoint = endingPoint;
		endingPoint = tempVec1;
	}

	tempVec1 = cocos2d::Vec2(0.0F, 0.0F) - cocos2d::Vec2((endingPoint - startingPoint) / 2); // gets the starting point of the graph with its centre at (0.0F, 0.0F)
	tempVec2 = cocos2d::Vec2(0.0F, 0.0F) + cocos2d::Vec2((endingPoint - startingPoint) / 2); // gets the ending point of the graph with its centre at (0.0F, 0.0F)

	startingPoint = tempVec1; // overrides the startingPoint so that it's in reference to the drawNode's origin (0.0F, 0.0F).
	endingPoint = tempVec2; // overrides the endingPoint so that it's in reference to the drawNode's origin (0.0F, 0.0F).

	// draws horizontal lines until the bounds of the grid are reached.
	for (float i = 0; startingPoint.y + i < endingPoint.y; i += squareSize)
		m_Node->drawLine(startingPoint + cocos2d::Vec2(0.0F, i), cocos2d::Vec2(endingPoint.x, startingPoint.y + i), colour); // draws a horizontal line

	// vertical lines until the bounds of the grid are reached.
	for (float i = 0; startingPoint.x + i < endingPoint.x; i += squareSize)
		m_Node->drawLine(startingPoint + cocos2d::Vec2(i, 0.0F), cocos2d::Vec2(startingPoint.x + i, endingPoint.y), colour); // draws a vertical line


	// if 'gridBox' is 'true', then a quadrilateral is drawn around the whole grid.
	if (gridBox)
		m_Node->drawRect(startingPoint, endingPoint, colour);

	m_Node->setPosition(POSITION); // sets the node to the position of the grid.
	m_Node->setGlobalZOrder(10.3F); // sets the global z order of the grid. This is different from the global z order of other primitives.

	/*
	cocos2d::Vec2 tempVec;
	m_Node->setAnchorPoint(cocos2d::Vec2(0.5F, 0.5F));

	if (startingPoint.x > endingPoint.x) // switches the start point and end point if the ending point is before the starting point.
	{
		tempVec = startingPoint;
		startingPoint = endingPoint;
		endingPoint = tempVec;
	}

	// draws horizontal lines until the bounds of the grid are reached.
	for (float i = 0; startingPoint.y + i < endingPoint.y; i += squareSize)
		m_Node->drawLine(startingPoint + cocos2d::Vec2(0.0F, i), cocos2d::Vec2(endingPoint.x, startingPoint.y + i), colour); // draws a horizontal line

	// vertical lines until the bounds of the grid are reached.
	for (float i = 0; startingPoint.x + i < endingPoint.x; i += squareSize)
		m_Node->drawLine(startingPoint + cocos2d::Vec2(i, 0.0F), cocos2d::Vec2(startingPoint.x + i, endingPoint.y), colour); // draws a vertical line


	// if 'gridBox' is 'true', then a quadrilateral is drawn around the whole grid.
	if (gridBox)
		m_Node->drawRect(startingPoint, endingPoint, colour);

	m_Position = startingPoint + (endingPoint - startingPoint) / 2; // gets the location of the primitive.
	*/
}

// creates a grid using a size and position instead of a starting point and ending point.
OOP::PrimitiveGrid::PrimitiveGrid(cocos2d::Vec2 position, cocos2d::Size size, const float squareSize, const cocos2d::Color4F colour, const bool gridBox)
	: OOP::PrimitiveGrid(cocos2d::Vec2(position - (size / 2)), cocos2d::Vec2(position + (size / 2)), squareSize, colour, gridBox)
{
	// the position is based on the middle of the grid
}

// releases the grid node.
OOP::PrimitiveGrid::~PrimitiveGrid() { /*m_Node->release();*/ }

// sets the position of the primitive.
void OOP::PrimitiveGrid::setPosition(cocos2d::Vec2 position)
{
	m_Node->setPosition(position);
	// because the position of the node isn't the same as the primitive itself, this calculation is needed.
	//m_Node->setPosition(m_Node->getPosition() + position - m_Position);
	//this->m_Position = position;
}
