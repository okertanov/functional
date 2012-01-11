/*!
	@file		dsie-ut.h 
	@brief		Unit Testing suite
	@author		oleh.kertanov@ua.flextronics.com
	@date		14.02.2006
	@version	0.3
	@note		This file exports macroses for the unittesting purposes.
	
				Copyright (C) 2006 oleh.kertanov@ua.flextronics.com
*/

#ifndef _DSIE_UT_H_INCLUDED_
#define _DSIE_UT_H_INCLUDED_

#include "core/dsie-config.h"
#include "core/dsie-types.h"


#define UT_START_SUITE_FORMATTER	"\n**********************************************************************\n\t%s\n**********************************************************************"
#define UT_START_TEST_FORMATTER		"\nUT: %s starting..."
#define UT_STOP_FORMATTER			"\nUT: %s done.\n"
#define UT_EVAL_FORMATTER			"\nUT: Evaluating %s: "
#define UT_TESTFAILED_FORMATTER		"\nUT: Expression \"%s\" failed in file: \nUT: %s:(%d) "
#define UT_EOF_EVAL_FORMATTER		"%s"
#define UT_EVAL_OK					" OK. "
#define UT_EVAL_FAILED				" FAILED. "
#define UT_EVAL_NOTHING				""

#ifdef UT_EMU_TARGET /*Development Platform (Win32)*/

#define UT_OUTPUT					printf
#define UT_INITSUITE(T)				UT_OUTPUT(UT_START_SUITE_FORMATTER, T)
#define UT_STARTTEST(T)				UT_OUTPUT(UT_START_TEST_FORMATTER, T)
#define UT_EVAL(E)					{BOOL utrv=E; UT_OUTPUT(UT_EVAL_FORMATTER, #E); UT_OUTPUT(UT_EOF_EVAL_FORMATTER,utrv?UT_EVAL_OK:UT_EVAL_FAILED);}
#define UT_TEST(E)					{if(!(E)) {UT_OUTPUT(UT_TESTFAILED_FORMATTER, #E, __FILE__, __LINE__);}}
#define UT_STOPTEST(T)				UT_OUTPUT(UT_STOP_FORMATTER, T)

#else /*HW Target Platform (Quallcom or its emulation)*/

#define UT_OUTPUT					{}
#define UT_INITSUITE(T)				{}
#define UT_STARTTEST(T)				{}
#define UT_EVAL(E)					{}
#define UT_TEST(E)					{}
#define UT_STOPTEST(T)				{}

#endif /*UT_EMU_TARGET*/


#endif /*_DSIE_UT_H_INCLUDED_*/
