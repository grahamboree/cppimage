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
	COLORREF macro_white = MACRO_RGB(255,255,255);

	TEST_ASSERT(white == macro_white);

	COLORREF red = RGB(255, 0, 0);
	COLORREF green = RGB(0, 255, 0);
	COLORREF blue = RGB(0, 0, 255);

	TEST_ASSERT(GetRValue(red) == 255);
	TEST_ASSERT(GetGValue(green) == 255);
	TEST_ASSERT(GetBValue(blue) == 255);
	std::cout << "blue = " << (unsigned short)(MACRO_GetBValue(blue)) << std::endl;
	
	COLORREF someColor = RGB(1,2,3);
	TEST_ASSERT(GetRValue(someColor) == MACRO_GetRValue(someColor));
	TEST_ASSERT(GetGValue(someColor) == MACRO_GetGValue(someColor));
	TEST_ASSERT(GetBValue(someColor) == MACRO_GetBValue(someColor));
	
	uint32_t testColorLayout = 0x00030201;
	TEST_ASSERT(memcmp(&testColorLayout, &someColor, sizeof(COLORREF)) == 0);
	
	int32_t redGreyscale = (int32_t)RGB2GRAY(GetRValue(red), GetGValue(red), GetBValue(red));
	int32_t macroRedGreyscale = (int32_t)MACRO_RGB2GRAY(GetRValue(red), GetGValue(red), GetBValue(red));
	
	TEST_ASSERT(redGreyscale == macroRedGreyscale);
}
