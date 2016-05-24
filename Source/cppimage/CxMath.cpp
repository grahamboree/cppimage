//
//  CxMath.cpp
//  cppimage
//
//  Created by Graham Pentheny on 11/10/12.
//  Copyright (c) 2012 Graham Pentheny. All rights reserved.
//

#include "CxMath.h"

namespace CppImage
{
	//////////////////////////////////////////////////////////////////////////
	/// Returns the intersection crossection with another rectangle or a 0 area
	///  rectangle if there is no overlap.
	/// @param[in] inRect
	Rect2 Rect2::CrossSection(const Rect2& inRect) const
	{
		Rect2 crossSection(
			max(botLeft.x,  inRect.botLeft.x),
			max(botLeft.y,  inRect.botLeft.y),
			min(topRight.x, inRect.topRight.x),
			min(topRight.y, inRect.topRight.y));

		if (crossSection.botLeft.x <= crossSection.topRight.x && crossSection.botLeft.y <= crossSection.topRight.y)
		{
			return crossSection;
		}
		// The resulting rect is not valid, so there is no overlap.
		return Rect2();
	}
}
