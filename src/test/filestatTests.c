#include "CuTest.h"
#include <stdio.h>

CuSuite *CuGetSuite();
CuSuite *CuStringGetSuite();

int RunAllTests(void) {
	CuString *output = CuStringNew();
	CuSuite *suite = CuSuiteNew();
	CuSuiteAddSuite(suite, filestatGetSuite());
	CuSuiteRun(suite);
	CuSuiteSummary(suite, output);
	CuSuiteDetails(suite, output);
	printf("%s\n", output->buffer);
	return suite->failCount;
}

int main(void) {
	return RunAllTests();
}