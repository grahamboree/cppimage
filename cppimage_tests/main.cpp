//
//  main.cpp
//  cppimage_tests
//
//  Created by Graham Pentheny on 11/11/12.
//  Copyright (c) 2012 Graham Pentheny. All rights reserved.
//

// STL
#include <iostream>
#include <memory>

// Test framework
#include "cpptest.h"

#define CPPIMAGE_TESTING
// Test suites
#include "TestCxDefines.h"

using namespace std;

//////////////////////////////////////////////////////////////////////////
int main()
{
	Test::TextOutput output(Test::TextOutput::Verbose);

	Test::Suite suite;
	suite.add(auto_ptr<Test::Suite>(new TestCxDefines));

	return suite.run(output);
}
