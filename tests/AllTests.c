#include "CuTest.h"
#include <stdio.h>

CuSuite *LibCharGetSuite();

int RunAllTests(void)
{
	CuString *output = CuStringNew();
	CuSuite *suite = CuSuiteNew();

	CuSuiteAddSuite(suite, LibCharGetSuite());

	CuSuiteRun(suite);
	CuSuiteSummary(suite, output);
	CuSuiteDetails(suite, output);

	printf("%s\n", output->buffer);
	return suite->failCount != 0;
}

int main(void)
{
	const int ret = RunAllTests();
	return ret;
}
