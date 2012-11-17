//
//  CxMath.h
//  cppimage
//
//  Created by Graham Pentheny on 11/10/12.
//  Copyright (c) 2012 Graham Pentheny. All rights reserved.
//

#pragma once

#include "CxDefines.h"

namespace CppImage
{
	//////////////////////////////////////////////////////////////////////////
	class DLL_EXP Point2
	{
	public:
		Point2();
		Point2(float inX, float inY);

		float Distance(const Point2& p2) const;
		float Distance(float inX, float inY) const;

		float x;
		float y;
	};
	/// @todo remove this.  Exists for compatibility.
	typedef Point2 CxPoint2;

	//////////////////////////////////////////////////////////////////////////
	class DLL_EXP Rect2
	{
	public:
		Rect2() {}
		Rect2(float inBotLeftX, float inBotLeftY, float inTopRightX, float inTopRightY);
		Rect2(const Point2& inBottomLeft, const Point2& inTopRight);

		float 	Area() const;
		Rect2 	CrossSection(const Rect2& inRect2) const;
		Point2 	Center() const;
		float	Width() const;
		float 	Height() const;

		Point2 botLeft;
		Point2 topRight;
	};
	/// @todo remove this.  Exists for compatibility.
	typedef Rect2 CxRect2;
}


namespace CppImage
{
	//////////////////////////////////////////////////////////////////////////
	/// Default constructs a point at the origin.
	inline Point2::Point2()
	: x(0.0f)
	, y(0.0f)
	{
	}

	//////////////////////////////////////////////////////////////////////////
	/// @param[in] inX The point's x coordinate.
	/// @param[in] inY The point's y coordinate.
	inline Point2::Point2(const float inX, const float inY)
	: x(inX)
	, y(inY)
	{
	}

	//////////////////////////////////////////////////////////////////////////
	/// @param[in] inPoint The other point.
	/// @returns The distance between this point and the other point.
	inline float Point2::Distance(const Point2& p2) const
	{
		return (float)sqrt((x - p2.x) * (x - p2.x) + (y - p2.y) * (y - p2.y));
	}

	//////////////////////////////////////////////////////////////////////////
	/// @param[in] inX The x coordinate of the other point.
	/// @param[in] inY The y coordinate of the other point.
	/// @returns The distance between this and the other point.
	inline float Point2::Distance(const float inX, const float inY) const
	{
		return (float)sqrt((x - inX) * (x - inX) + (y - inY) * (y - inY));
	}

	//////////////////////////////////////////////////////////////////////////
	/// @param[in] inLeft	The rect's minimum x extent.
	/// @param[in] inBottom The rect's minimum y extent.
	/// @param[in] inRight	The rect's maximum x extent.
	/// @param[in] inTop	The rect's maximum y extent.
	inline Rect2::Rect2(const float inLeft, const float inBottom, const float inRight, const float inTop)
	: botLeft(inLeft, inBottom)
	, topRight(inRight, inTop)
	{
	}

	//////////////////////////////////////////////////////////////////////////
	/// @param[in] inBototmLeft The bottom left corner of the rectangle.
	/// @param[in] inTopRight The top right corner of the rectangle.
	inline Rect2::Rect2(const Point2& inBottomLeft, const Point2& inTopRight)
	: botLeft(inBottomLeft)
	, topRight(inTopRight)
	{
	}

	//////////////////////////////////////////////////////////////////////////
	/// @returns The area of the rectangle.
	inline float Rect2::Area() const
	{
	  return (topRight.x - botLeft.x) * (topRight.y - botLeft.y);
	}

	//////////////////////////////////////////////////////////////////////////
	/// @returns The center point of rectangle.
	inline Point2 Rect2::Center() const
	{
		return Point2((topRight.x + botLeft.x) / 2.0f, (topRight.y + botLeft.y) / 2.0f);
	}

	//////////////////////////////////////////////////////////////////////////
	/// @returns The rectangle width.
	inline float Rect2::Width() const
	{
		return topRight.x - botLeft.x;
	}

	//////////////////////////////////////////////////////////////////////////
	/// @returns The rectangle height.
	inline float Rect2::Height() const
	{
		return topRight.y - botLeft.y;
	}
}
