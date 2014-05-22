#include "../main/filestat.c"
#include "CuTest.h"


void testGetNextLine_BlankFile(CuTest *tc) {
	inStream = fopen("data/test/File_AllBlanks.txt", "r");
	struct linestat *nxtLine = (struct linestat *)malloc(sizeof(struct linestat));
	int lines = getNextLine(nxtLine, 0);
	fclose(inStream);
	CuAssertIntEquals(tc, -1, nxtLine->lineno);
	CuAssertStrEquals(tc, NULL, nxtLine->line);
	free(nxtLine);
}

void testGetNextLine_Oneline(CuTest *tc) {
	inStream = fopen("data/test/File_Oneline.txt", "r");
	struct linestat *nxtLine = (struct linestat *)malloc(sizeof(struct linestat));
	int lines = getNextLine(nxtLine, 1);
	fclose(inStream);
	CuAssertIntEquals(tc, 1, nxtLine->lineno);
	CuAssertStrEquals(tc, "I am Santanu", nxtLine->line);
	free(nxtLine);
}

void testGetNextLine_OnelineMiddle(CuTest *tc) {
	inStream = fopen("data/test/File_OnelineMiddle.txt", "r");
	struct linestat *nxtLine = (struct linestat *)malloc(sizeof(struct linestat));
	int lines = getNextLine(nxtLine, 1);
	CuAssertIntEquals(tc, 2, nxtLine->lineno);
	CuAssertStrEquals(tc, "I am Santanu", nxtLine->line);
	free(nxtLine);
	nxtLine = (struct linestat *)malloc(sizeof(struct linestat));
	lines = getNextLine(nxtLine, 0);
	fclose(inStream);
	CuAssertIntEquals(tc, -1, nxtLine->lineno);
	CuAssertStrEquals(tc, NULL, nxtLine->line);
	free(nxtLine);
}

CuSuite *filestatGetSuite() {
	CuSuite *suite = CuSuiteNew();
	SUITE_ADD_TEST(suite, testGetNextLine_BlankFile);
	SUITE_ADD_TEST(suite, testGetNextLine_Oneline);
	SUITE_ADD_TEST(suite, testGetNextLine_OnelineMiddle);
	return suite;
}