/*!
	@file		dsie-ut-runner.c 
	@brief		Unit Testing suite runner module
	@author		oleh.kertanov@ua.flextronics.com
	@date		14.02.2006
	@version	0.3
	@note		Executes testcases.
	
				Copyright (C) 2006 oleh.kertanov@ua.flextronics.com
*/

#include "dsie-ut.h"
#include "dsie-ut-runner.h"

/*External Test Suites*/
extern BOOL SimpleScenarioTestSuite();
extern BOOL DSIeAlgorithmTestSuite();
extern BOOL MatrixVectorTestSuite();
extern BOOL MathOperatorsTestSuite();
extern BOOL CoreTypesTestSuite();

/*Runner - plain C-main*/
int main(int argc, char** argv)
{
	SimpleScenarioTestSuite();
	
	CoreTypesTestSuite();

	MatrixVectorTestSuite();
	
	MathOperatorsTestSuite();
	
	DSIeAlgorithmTestSuite();

	return 0;
}
