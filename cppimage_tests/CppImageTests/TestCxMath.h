//
//  TestCxMath.h
//  cppimage
//
//  Created by Graham Pentheny on 11/10/12.
//  Copyright (c) 2012 Graham Pentheny. All rights reserved.
//

#pragma once

#include "cpptest.h"

#include "CxMath.h"

using namespace CppImage;

//////////////////////////////////////////////////////////////////////////
class TestCxMath : public Test::Suite 
{
public:
	TestCxMath()
	{
		TEST_ADD(TestCxMath::TestPoint2);
		TEST_ADD(TestCxMath::TestRect2);
	}
private:
	void TestPoint2();
	void TestRect2();
};

//////////////////////////////////////////////////////////////////////////
inline void TestCxMath::TestPoint2()
{
	Point2 defaultCtor;
	TEST_ASSERT_DELTA(defaultCtor.x, 0.0f, kFloatEpsilon);
	TEST_ASSERT_DELTA(defaultCtor.y, 0.0f, kFloatEpsilon);
	
	Point2 testPoint(1.0f, 2.0f);
	TEST_ASSERT_DELTA(testPoint.x, 1.0f, kFloatEpsilon);
	
	Point2 origin(0.0f, 0.0f);
	Point2 hypotenuse(3.0f, 4.0f);
	TEST_ASSERT_DELTA(hypotenuse.Distance(origin), 5.0f, kFloatEpsilon);
	
	Point2 rightThree(3.0f, 0.0f);
	TEST_ASSERT_DELTA(rightThree.Distance(origin), 3.0f, kFloatEpsilon);
}

//////////////////////////////////////////////////////////////////////////
inline void TestCxMath::TestRect2()
{
	Rect2 oneByOne(0.0f, 1.0f, 2.0f, 3.0f);
	TEST_ASSERT_DELTA(oneByOne.botLeft.x, 0.0f, kFloatEpsilon);
	TEST_ASSERT_DELTA(oneByOne.botLeft.y, 1.0f, kFloatEpsilon);
	TEST_ASSERT_DELTA(oneByOne.topRight.x, 2.0f, kFloatEpsilon);
	TEST_ASSERT_DELTA(oneByOne.topRight.y, 3.0f, kFloatEpsilon);
	
	Point2 bLeft(-1.0f, -3.0f);
	Point2 tRight(2.0f, 3.5f);
	Rect2 someRect(bLeft, tRight);
	TEST_ASSERT_DELTA(bLeft.x, someRect.botLeft.x, kFloatEpsilon);
	TEST_ASSERT_DELTA(bLeft.y, someRect.botLeft.y, kFloatEpsilon);
	TEST_ASSERT_DELTA(tRight.x, someRect.topRight.x, kFloatEpsilon);
	TEST_ASSERT_DELTA(tRight.y, someRect.topRight.y, kFloatEpsilon);
	
	// Test Center().
	Point2 computedCenter = someRect.Center();
	TEST_ASSERT_DELTA(computedCenter.x, bLeft.x + someRect.Width() / 2.0f, kFloatEpsilon);
	TEST_ASSERT_DELTA(computedCenter.y, bLeft.y + someRect.Height() / 2.0f, kFloatEpsilon);
	
	// Test Width().
	TEST_ASSERT_DELTA(someRect.Width(), tRight.x - bLeft.x, kFloatEpsilon);
	
	// Test Height().
	TEST_ASSERT_DELTA(someRect.Height(), tRight.y - bLeft.y, kFloatEpsilon);
	
	// Test CrossSection().
	Rect2 rectOne(0.0f, 0.0f, 2.0f, 2.0f);
	Rect2 rectTwo(-1.0f, -1.0f, 1.0f, 1.0f);
	Rect2 crossSection = rectOne.CrossSection(rectTwo);
	
	TEST_ASSERT_DELTA(crossSection.botLeft.x, 0.0f, kFloatEpsilon);
	TEST_ASSERT_DELTA(crossSection.botLeft.y, 0.0f, kFloatEpsilon);
	TEST_ASSERT_DELTA(crossSection.topRight.x, 1.0f, kFloatEpsilon);
	TEST_ASSERT_DELTA(crossSection.topRight.y, 1.0f, kFloatEpsilon);
	
	TEST_ASSERT_DELTA(rectOne.Area(), 4.0f, kFloatEpsilon);
}
