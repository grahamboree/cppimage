#include "CxImage.h"
#include "ximath.h"
#include <math.h>

//this module should contain some classes for geometrical transformations
//usable with selections, etc... once it's done, that is. :)

//////////////////////////////////////////////////////////////////////////
CxRect2 CxRect2::CrossSection(const CxRect2& inRect2) const
/*
 * Returns crossection with another rectangle.
 */
{
	CxRect2 cs;
	cs.botLeft.x = max(botLeft.x, inRect2.botLeft.x);
	cs.botLeft.y = max(botLeft.y, inRect2.botLeft.y);
	cs.topRight.x = min(topRight.x, inRect2.topRight.x);
	cs.topRight.y = min(topRight.y, inRect2.topRight.y);
	if (cs.botLeft.x <= cs.topRight.x && cs.botLeft.y <= cs.topRight.y)
	{
		return cs;
	}
	else
	{
		return CxRect2(0,0,0,0);
	}
}
