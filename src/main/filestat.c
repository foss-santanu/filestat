#include <ctype.h>
#include "filestat.h"

#ifdef TEST_FILESTAT
int main_t(int argc, char const *argv[]) {
#else
int main(int argc, char const *argv[]) {
#endif
	int totalCharCount = 0, /* total count of non-blank characters */
	    totalWordCount = 0, /* total word count of the file */
	    totalLineCount = 0; /* total count of non-blank lines in the file */

	/* parse command-line arguments */
	if (argc == 1) {
		printf("Usage: %s [options] [filepath]\n\nOptions:\n\n\t-c\tInput from console.\n\t-f\tInput from file <filepath>\n",
		       argv[0]);
		exit(0);
	}
	else if (argc > 1) {
		if (argv[1][0] == '-') {
			switch (argv[1][1]) {
				case 'c': /* take input from console */
					inStream = stdin;
					break;

				case 'f': /* take input from file if specified */
					if (argc == 3) {
						inStream = fopen(argv[2], "r");
						break;
					}
					else {
						printf("Error invoking %s: No file to read.\n", argv[0]);
						exit(0);
					}

				default: /* Unknown option */
					printf("Error invoking %s: Unknown option\n", argv[0]);
					exit(0);
			}
		}
		else {
			printf("Error invoking %s: Incorrect option specification.\n", argv[0]);
			exit(0);
		}
	}

	/* Read next line from input and calculate statistics */
	maxline = NULL; /* initialize maxline */

	while (1) {
		struct linestat *nxtLine = (struct linestat *)malloc(sizeof(struct linestat));

		if (nxtLine == NULL) {
			printf("Error in %s: Out of memory\n", argv[0]);
			exit(1);
		}

		int linesRead = getNextLine(nxtLine, 0);

		if (nxtLine->line != NULL) { /* not EOF */
			totalCharCount += nxtLine->charCount;
			totalWordCount += nxtLine->wordCount;
			totalLineCount++;

			if (maxline == NULL || nxtLine->charCount > maxline->charCount) {
				/* nxtLine is the longest line so far */
				maxline = nxtLine;
			}
			else {
				free(nxtLine);
			}
		}
		else { /* EOF */
			free(nxtLine);
			printf("%s: Reading input file complete\n", argv[0]);
			break;
		}
	}

	/* print statistics */
	printf("%s Results: \n\nTotal words .......... %d\nTotal characters ..... %d\nNon-blank lines ...... %d\n\n",
	       argv[0], totalWordCount, totalCharCount, totalLineCount);
	printf("Longest line found at line number %d: \n%s\n\n", maxline->lineno,
	       maxline->line);
	printf("Line statistics: \n\nCharacter count ....... %d\nWord count ............ %d\n",
	       maxline->charCount, maxline->wordCount);
	return 0;
}

int getNextLine(struct linestat *nxtLine, int reset) {
	if (nxtLine == NULL) {
		printf("Error in getNextLine: no space to save next line statistics\n");
		exit(2);
	}

	static int lineno = 0; /* no. of lines read so far */

	if (reset) {
		lineno = 0;
	}

	int i, c, /* next character from the file */
	    charCount = 0,
	    wordCount = 0;
	int isInsideWord = 0; /* state flag: c is read from same word */
	char *line = (char *)malloc(MAXLENGTH + 1); /* buffer for next line */

	if (line == NULL) {
		printf("Error in getNextLine: buffer to read lines cannot be allocated\n");
		exit(2);
	}

	while (1) {
		if (feof(inStream)) {
			nxtLine->line = NULL;
			nxtLine->lineno = -1;
			nxtLine->charCount = 0;
			nxtLine->wordCount = 0;
			break;
		}
		else {
			lineno++;

			for (i = 0; (c = fgetc(inStream)) != EOF && c != '\n' && i < MAXLENGTH; i++) {
				line[i] = c;

				if (!isspace(c)) { /* non-blank character */
					charCount++;

					if (!isInsideWord) { /* start of new word */
						isInsideWord = 1;
						wordCount++;
					}
				}
				else if (isInsideWord) { /* end of a word */
					isInsideWord = 0;
				}
			}

			if (i == MAXLENGTH && c != EOF && c != '\n') {
				printf("Error in getNextLine: too long line at line number %d\n", lineno);
				exit(2);
			}
			else if (charCount > 0) { /* non-blank line found */
				line[i] = '\0';
				nxtLine->line = line;
				nxtLine->lineno = lineno;
				nxtLine->charCount = charCount;
				nxtLine->wordCount = wordCount;
				break;
			}
		}
	}

	if (nxtLine->line == NULL) { /* EOF: free buffer for next line */
		free(line);
	}

	return lineno;
}