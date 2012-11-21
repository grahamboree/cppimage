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
		TEST_ADD(TestCxDefines::testColorRef);
		TEST_ADD(TestCxDefines::testRGB2GRAY);
	}
private:
	void testColorRef();
	void testRGB2GRAY();
};

//////////////////////////////////////////////////////////////////////////
inline void TestCxDefines::testColorRef()
{
	// Test that the template version works the same as the original macro version.
	ColorRef white = RGB(255,255,255);
	ColorRef macro_white = MACRO_RGB(255,255,255);

	TEST_ASSERT(white == macro_white);

	// Test the Get_Value functions...
	ColorRef red = RGB(255, 0, 0);
	ColorRef green = RGB(0, 255, 0);
	ColorRef blue = RGB(0, 0, 255);

	TEST_ASSERT(GetRValue(red) == 255);
	TEST_ASSERT(GetGValue(green) == 255);
	TEST_ASSERT(GetBValue(blue) == 255);
	
	// Test that the function values work the same as the macro values.
	ColorRef someColor = RGB(1,2,3);
	TEST_ASSERT(GetRValue(someColor) == MACRO_GetRValue(someColor));
	TEST_ASSERT(GetGValue(someColor) == MACRO_GetGValue(someColor));
	TEST_ASSERT(GetBValue(someColor) == MACRO_GetBValue(someColor));
	
	// Make sure the layout in memory is the same.
	uint32_t testColorLayout = 0x00030201;
	TEST_ASSERT(memcmp(&testColorLayout, &someColor, sizeof(ColorRef)) == 0);
}

//////////////////////////////////////////////////////////////////////////
inline void TestCxDefines::testRGB2GRAY()
{
	ColorRef red = RGB(255, 0, 0);
	
	// Test that the grayscale function works the same as the macro greyscale function.
	int32_t redGreyscale = (int32_t)RGB2GRAY(GetRValue(red), GetGValue(red), GetBValue(red));
	int32_t macroRedGreyscale = (int32_t)MACRO_RGB2GRAY(GetRValue(red), GetGValue(red), GetBValue(red));
	
	TEST_ASSERT(redGreyscale == macroRedGreyscale);
}


