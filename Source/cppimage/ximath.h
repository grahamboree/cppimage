#pragma once

#include "ximadef.h"

//////////////////////////////////////////////////////////////////////////
class DLL_EXP CxPoint2
{
public:
	CxPoint2();
	CxPoint2(const float inX, const float inY);
	CxPoint2(const CxPoint2& inPoint);

	float Distance(const CxPoint2& p2) const;
	float Distance(float inX, float inY) const;

	float x;
	float y;
};

//////////////////////////////////////////////////////////////////////////
class DLL_EXP CxRect2
{
public:
	CxRect2();
	CxRect2(const float inBotLeftX, const float inBotLeftY, const float inTopRightX, const float inTopRightY);
	CxRect2(CxPoint2 const& bl, CxPoint2 const& tr);
	CxRect2(const CxRect2& inRect);

	float 	Surface() const;
	CxRect2 	CrossSection(const CxRect2& inRect2) const;
	CxPoint2 	Center() const;
	float		Width() const;
	float 	Height() const;

	CxPoint2 botLeft;
	CxPoint2 topRight;
};

//////////////////////////////////////////////////////////////////////////
inline CxPoint2::CxPoint2()
: x(0.0f)
, y(0.0f)
{
}

//////////////////////////////////////////////////////////////////////////
inline CxPoint2::CxPoint2(const float inX, const float inY)
: x(inX)
, y(inY)
{
}

//////////////////////////////////////////////////////////////////////////
inline CxPoint2::CxPoint2(const CxPoint2& inPoint)
: x(inPoint.x)
, y(inPoint.y)
{
}

//////////////////////////////////////////////////////////////////////////
inline float CxPoint2::Distance(const CxPoint2& p2) const
{
	return (float)sqrt((x - p2.x) * (x - p2.x) + (y - p2.y) * (y - p2.y));
}

//////////////////////////////////////////////////////////////////////////
inline float CxPoint2::Distance(float inX, float inY) const
{
	return (float)sqrt((x - inX) * (x - inX) + (y - inY) * (y - inY));
}

//////////////////////////////////////////////////////////////////////////
inline CxRect2::CxRect2()
{
}

//////////////////////////////////////////////////////////////////////////
inline CxRect2::CxRect2(const float inBotLeftX, const float inBotLeftY, const float inTopRightX, const float inTopRightY)
: botLeft(inBotLeftX, inBotLeftY)
, topRight(inTopRightX, inTopRightY)
{
}

//////////////////////////////////////////////////////////////////////////
inline CxRect2::CxRect2(const CxRect2& inRect)
: botLeft(inRect.botLeft)
, topRight(inRect.topRight)
{
}

//////////////////////////////////////////////////////////////////////////
inline CxRect2::CxRect2(const CxPoint2& inBottomLeft, const CxPoint2& inTopRight)
: botLeft(inBottomLeft)
, topRight(inTopRight)
{
}

//////////////////////////////////////////////////////////////////////////
inline float CxRect2::Surface() const
/*
 * Returns the surface of rectangle.
 */
{
  return (topRight.x - botLeft.x) * (topRight.y - botLeft.y);
}

//////////////////////////////////////////////////////////////////////////
inline CxPoint2 CxRect2::Center() const
/*
 * Returns the center point of rectangle.
 */
{
	return CxPoint2((topRight.x + botLeft.x) / 2.0f, (topRight.y + botLeft.y) / 2.0f);
}

//////////////////////////////////////////////////////////////////////////
inline float CxRect2::Width() const
//returns rectangle width
{
	return topRight.x - botLeft.x;
}

//////////////////////////////////////////////////////////////////////////
inline float CxRect2::Height() const
//returns rectangle height
{
	return topRight.y - botLeft.y;
}

