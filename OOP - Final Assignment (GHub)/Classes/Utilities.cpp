#include "Utilities.h"
#include <math.h>

/// STRING AND GENERAL FUNCTIONS //////////////////////////////////////////////////////
std::string ustd::toLower(std::string str)
{
	// returns the string if its of length zero.
	if (str.length() == 0)
		return str;

	std::string strL; // temporary string
	strL.assign(str); // copies original string

	for (int i = 0; i < strL.length(); i++)
	{
		strL.at(i) = tolower(strL.at(i)); // converts each 'char' to its lowercase version if applicable
	}

	return strL;
}

// converts a whole string to uppercase
std::string ustd::toUpper(std::string str)
{
	// returns the string if its of length zero.
	if (str.length() == 0)
		return str;

	std::string strL; // temporary string
	strL.assign(str); // copies original string

	for (int i = 0; i < strL.length(); i++)
	{
		strL.at(i) = toupper(strL.at(i)); // converts each 'char' to its uppercase version if applicable
	}

	return strL;
}

// capitalizes a string.
std::string ustd::captialize(std::string str)
{
	// returns the string if its of length zero.
	if (str.length() == 0)
		return str;

	std::string strL; // temporary string
	strL.assign(str); // copies original string

	str = toLower(str); // makes the string all lowercase
	str.at(0) = toupper(str.at(0)); // capitalizes the first letter

	return strL;
}

// checks if two strings are equal, ignoring case diffrences.
bool ustd::equalsIgnoreCase(std::string str1, std::string str2)
{
	// making both strings lowercase
	str1 = toLower(str1);
	str2 = toLower(str2);
	return str1 == str2; // returning whether the two are equal
}

// checks if a string is an integer.
bool ustd::isInt(std::string str)
{
	int strInt; // gets the string as an int.
	std::stringstream ss(str); // creates a string stream for converting the string to an integer.

	ss >> strInt; // puts the string stream into the integer. If non-int values exist, then the int is truncated.

	return std::to_string(strInt) == str; // returns 'true' if all values were carried over from the string.
}

// checks if a string is a decimal number (specifically a double).
bool ustd::isDecimal(std::string str)
{
	double strDbl; // gets the string as an float
	std::stringstream ss(str); // creates a string stream for converting the string to an integer.

	ss >> strDbl; // puts the string stream into the double. If non-int values exist, then the doubleis truncated.

	return std::to_string(strDbl) == str; // returns 'true' if all values were carried over from the string.
}

/// MATH /////////////////////////////////////////////////////////////////////////////

// returns true if two circles are colliding or touching.
bool umath::circleCollision(Vec2 pos1, float radius1, Vec2 pos2, float radius2)
{
	int dist = sqrt(pow(pos2.x - pos1.x, 2) + pow(pos2.y - pos1.y, 2)); // calculates the distance between the two circles.
	return (dist <= radius1 + radius2);	
}

// calculates AABB collision with two rectangles based on a passed minimum and maximum value for both.
// Takes the minimum and maximum of the two rectangles.
bool umath::aabbCollision(const Vec2 aMin, const Vec2 aMax, const Vec2 bMin, const Vec2 bMax)
{
	// booleans for collision checks
	bool xCol, yCol;

	// xCol gets the result of this collision check. If the projection on the x-axis shows collision, then xCol is set to true.
	xCol = ((bMin.x > aMin.x && bMin.x < aMax.x) ^ (aMin.x > bMin.x && aMin.x < bMax.x));

	//  yCol gets the result of this collision check. If the projection on the y-axis shows collision, yCol is set to true.
	yCol = ((bMin.y > aMin.y && bMin.y < aMax.y) ^ (aMin.y > bMin.y && aMin.y < bMax.y));

	// if the x-collision and y-collision return positive, then there is collision.
	return (xCol && yCol);
}

// calls another aabb function to do the collision.
bool umath::aabbCollision(const Vec2 topLeftA, const Vec2 topRightA, const Vec2 bottomLeftA, const Vec2 bottomRightA, const Vec2 topLeftB, const Vec2 topRightB, const Vec2 bottomLeftB, const Vec2 bottomRightB)
{
	Vec2 aMin(bottomLeftA), aMax(topRightA); // the minimum and maximum values of the first rectangle (rect A).
	Vec2 bMin(bottomLeftB), bMax(topRightB); // the minimum and maximum values of the second rectangle (rect B).
	
	return aabbCollision(aMin, aMax, bMin, bMax);
}

// calculates rectnagle collision using two cocos2d rectangles
bool umath::aabbCollision(const Rect * rect1, const Rect * rect2)
{
	return rect1->intersectsRect(*rect2);
	// Reuses the other collison check. It originally had its own algorithm, which is shwon below.
	//return umath::aabbCollision(Vec2(rect1->getMinX(), rect1->getMinY()), Vec2(rect1->getMaxX(), rect1->getMaxY()), Vec2(rect2->getMinX(), rect2->getMinY()), Vec2(rect2->getMaxX(), rect2->getMaxY()));
}

// calculates obb collision between two rectangles; this assumes that the rotation angles are based on the middle of the rectangles.
// These calculations require that the angle is put into radians, but since cocos2d inherently uses degrees, 'isRadians' needs to check what form the angle is in.
bool umath::obbCollision(Rect & rectA, float angleA, Rect & rectB, float angleB, bool inDegrees)
{
	// if the angles have been provided in degrees, then they are converted to radians for the rotation calculations.
	if (inDegrees) // converts angle A and B into radians.
	{ 
		angleA = umath::degreesToRadians(angleA);
		angleB = umath::degreesToRadians(angleB);
	}

	return umath::obbCollision(Vec2(rectA.getMinX(), rectA.getMaxY()), Vec2(rectA.getMaxX(), rectA.getMaxY()), Vec2(rectA.getMinX(), rectA.getMinY()), Vec2(rectA.getMaxX(), rectA.getMinY()), angleA,
							   Vec2(rectB.getMinX(), rectB.getMaxY()), Vec2(rectB.getMaxX(), rectB.getMaxY()), Vec2(rectB.getMinX(), rectB.getMinY()), Vec2(rectB.getMaxX(), rectB.getMinY()), angleB
	);
}

// obb collision function. If IS_ROTATED is false, then the program rotates the two rectangles before doing any collision checks.
bool umath::obbCollision(const Vec2 topLeftA, const Vec2 topRightA, const Vec2 bottomLeftA, const Vec2 bottomRightA, const float thetaA, const Vec2 topLeftB, const Vec2 topRightB, const Vec2 bottomLeftB, const Vec2 bottomRightB, const float thetaB, const bool IS_ROTATED)
{
	Vec2 posA = ((bottomLeftA + topRightA) / 2); // the position of rectangle A
	Vec2 posB = ((bottomLeftB + topRightB) / 2); // the position of rectangle B
	Vec2 rPos = (posA + posB) / 2; // the centre position that the two rectangles are rotated around.

	// makes copies of all the passed vector values.
	Vec2 tempTLA(topLeftA), tempTRA(topRightA), tempBLA(bottomLeftA), tempBRA(bottomRightA);
	Vec2 tempTLB(topLeftB), tempTRB(topRightB), tempBLB(bottomLeftB), tempBRB(bottomRightB);

	bool intersects = false; // saves the results of intersection checks.

	if (IS_ROTATED == false) // if the boxes have not been rotated, the function does so around their centre
	{
		tempTLA = umath::rotate(topLeftA - posA, thetaA) + posA;
		tempTRA = umath::rotate(topRightA - posA, thetaA) + posA;
		tempBLA = umath::rotate(bottomLeftA - posA, thetaA) + posA;
		tempBRA = umath::rotate(bottomRightA - posA, thetaA) + posA;

		tempTLB = umath::rotate(topLeftB - posB, thetaB) + posB;
		tempTRB = umath::rotate(topRightB - posB, thetaB) + posB;
		tempBLB = umath::rotate(bottomLeftB - posB, thetaB) + posB;
		tempBRB = umath::rotate(bottomRightB - posB, thetaB) + posB;
	}

	// checks for collision with rectangle A aligned with the axis.
	intersects = aabbCollision(
		umath::rotate(tempTLA - rPos, -thetaA) + rPos, umath::rotate(tempTRA - rPos, -thetaA) + rPos, umath::rotate(tempBLA - rPos, -thetaA) + rPos, umath::rotate(tempBRA - rPos, -thetaA) + rPos,
		umath::rotate(tempTLB - rPos, -thetaA) + rPos, umath::rotate(tempTRB - rPos, -thetaA) + rPos, umath::rotate(tempBLB - rPos, -thetaA) + rPos, umath::rotate(tempBRB - rPos, -thetaA) + rPos
	);

	if (intersects == false) // if there was no intersection, a false is returned.
		return false;

	// checks for collision with rectangle B aligned with the axis.
	intersects = aabbCollision(
		umath::rotate(tempTLA - rPos, -thetaB) + rPos, umath::rotate(tempTRA - rPos, -thetaB) + rPos, umath::rotate(tempBLA - rPos, -thetaB) + rPos, umath::rotate(tempBRA - rPos, -thetaB) + rPos,
		umath::rotate(tempTLB - rPos, -thetaB) + rPos, umath::rotate(tempTRB - rPos, -thetaB) + rPos, umath::rotate(tempBLB - rPos, -thetaB) + rPos, umath::rotate(tempBRB - rPos, -thetaB) + rPos
	);

	// if intersects is true, then there is collision. If not, then there is no intersection.
	return intersects;
}

// checks collision between an aabb and a circle using built in cocos algorithms.
bool umath::aabbCircleCollision(const Rect & rect, const Vec2 circlePos, const float radius) { return rect.intersectsCircle(circlePos, radius); }

// converts from degrees to radians
float umath::degreesToRadians(float degrees) { return degrees * (M_PI / 180); }

// converts from radians to degrees
float umath::radiansToDegrees(float radians) { return radians * (180 / M_PI); }

// a rotation function. While it doesn't use a rotation matrix, it's modeled after how one would be used for a rotation.
//  The angle is IN RADIANS.
Vec2 umath::rotate(Vec2 points, float angle, bool inDegrees)
{
	// rotates the coordinate points using a rotation matrix. Well, it technically ISN'T using a matrix, but it's modeled after how two matrices would be multiplied with one another.
	// This uses a rotation matrix setup, which is modeled below. With matricies, the calculation would be done in the way shown below, which is what was harcoded below.
	// [ cos a , -sin a] [x] = [ xcos a - ysin a ]
	// [ sin a ,  cos a] [y] = [ xsin a + ycos a ]

	if (inDegrees) // if the angle provided is in degrees, it's converted to radians.
		angle = umath::degreesToRadians(angle);

	return cocos2d::Vec2(points.x * (cosf(angle)) - points.y * (sinf(angle)), points.x * (sinf(angle)) + points.y * (cosf(angle)));
}

// generates a random integer
int umath::randInt(int lBound, int uBound, bool includeUBound)
{
	int tempInt(0);
	int randInt(0);
	// If the upper and lower bounds on the same, it returns the lBound
	if (lBound == uBound)
	{
		return lBound;
	}
	// If the lower bound is greater than the upper bound, they are swapped
	else if (lBound > uBound)
	{
		tempInt = lBound;
		lBound = uBound;
		uBound = tempInt;
	}

	// If the upperbound is positive, the values can be used as is.
	// If the upperbound and lowerbound are both negative, then a randomizer is run to get their absoluted range, then another randomizer is run to make it positive or negative.

	randInt = (uBound > 0) ? rand() % (uBound - lBound + includeUBound) + lBound : (abs(uBound) - abs(lBound) + includeUBound) + abs(lBound);

	// If the number must be negative, it is multiplied by -1 to make it so.
	if (lBound < 0 && uBound < 0)
		randInt *= -1;
	randInt = rand() % (uBound - lBound + includeUBound) + lBound;

	return randInt;
}
