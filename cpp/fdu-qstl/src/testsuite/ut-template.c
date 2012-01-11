/*!
	@file		unit-template.c 
	@brief		Unit Testing suite Test case example
	@author		oleh.kertanov@ua.flextronics.com
	@date		14.02.2006
	@version	0.3
	@note		Shown how to use test suite.
	
				Copyright (C) 2006 oleh.kertanov@ua.flextronics.com
*/

#include "dsie-ut.h"
#include "unit-template.h"

BOOL SimpleScenarioTestSuite(void);

static BOOL Test1(void* lpData);
static BOOL Test2(void* lpData);
static BOOL Test3(void* lpData);

BOOL SimpleScenarioTestSuite()
{
	UT_INITSUITE("Simple (Internal UT) Scenario");

	UT_STARTTEST("UT Framework Self Test");
	UT_EVAL( TRUE );
	UT_EVAL( FALSE );
	UT_STOPTEST("UT Framework Self Test");

	UT_STARTTEST("Simple Test Case");
	UT_EVAL( Test1(NULL) );
	UT_EVAL( Test2(NULL) );
	UT_EVAL( Test3(NULL) );
	UT_STOPTEST("Simple Test Case");

	return TRUE;
}

BOOL Test1(void* lpData)
{
	UT_TEST( TRUE == Func1(TRUE) ); 
	
	return TRUE;
}

BOOL Test2(void* lpData)
{
	UT_TEST( 1 == Func2(0) );
	UT_TEST( FALSE );

	return TRUE;
}

BOOL Test3(void* lpData)
{
	Func3();

	return TRUE;
}
