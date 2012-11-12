//
//  TestCxDefines.h
//  cppimage
//
//  Created by Graham Pentheny on 11/10/12.
//  Copyright (c) 2012 Graham Pentheny. All rights reserved.
//

#pragma once

#include "cpptest.h"

#include "CxDefines.h"

//////////////////////////////////////////////////////////////////////////
class TestCxDefines : public Test::Suite
{
public:
	TestCxDefines()
	{
		TEST_ADD(TestCxDefines::testRGB);
	}
private:
	void testRGB();
};

//////////////////////////////////////////////////////////////////////////
inline void TestCxDefines::testRGB()
{
	COLORREF white = RGB(255,255,255);
	(void)white;
}
