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
	CxRect2 CxRect2::CrossSection(const CxRect2& inRect) const
	{
		CxRect2 crossSection;
		crossSection.botLeft.x  = max(botLeft.x,  inRect.botLeft.x);
		crossSection.botLeft.y  = max(botLeft.y,  inRect.botLeft.y);
		crossSection.topRight.x = min(topRight.x, inRect.topRight.x);
		crossSection.topRight.y = min(topRight.y, inRect.topRight.y);
		if (crossSection.botLeft.x <= crossSection.topRight.x && crossSection.botLeft.y <= crossSection.topRight.y)
		{
			return crossSection;
		}
		else
		{
			return CxRect2(0,0,0,0);
		}
	}
}
