#include <stdio.h>
#include <stdlib.h>

#ifndef  _FILESTAT_H
#define _FILESTAT_H
#ifdef __cplusplus
extern "C" {
#endif

/* statistics for the current longest line */
struct linestat {
	char *line; /* characters in a line - without \n */
	int lineno; /* line number in the file */
	int charCount; /* count of non-blank characters in the line */
	int wordCount; /* word count of the line */
};

static struct linestat *maxline = NULL; /* current longest line */
static const int MAXLENGTH = 1024; /* maximum character length of a line */
static FILE *inStream; /* input file */

/*
 *    Function: getNextLine
 *    ----------------------
 *
 *    Reads next non-blank line from input file inStream.
 *
 *    nxtLine: pointer to struct linestat;
 *             next non-blank line if found in the file
 *             nxtLine->line is NULL if EOF
 *    reset: reset lineno, at start 0
 *
 *    returns: number of lines (blank and non-blank) read so far
 *
 */

int getNextLine(struct linestat *nxtLine, int reset);

#ifdef __cplusplus
}
#endif
#endif