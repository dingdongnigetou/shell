/*
 * 2014 (C) HuangJinDong
 *
 * scan.c
 *
 * The scanner implementmtion ofr the ddsh.
 *
 */

#include "globals.h"
#include "scan.h"

/* states in scanner DFA */
typedef enum{
	/* will be add more */
	INCOMMAND, INPARAM, INCOMMENT, DONE
}StateTypes;

/* the length of the input buffer for source code lines */
#define BUFLEN 256

static char linebuf[BUFLEN]; /* holds the current line */
static int  linepos = 0;     /* current position in linebuf */
static int  bufsize = 0;     /* current size of buffer string */

/* 
 * getNextChar fetches the next non-blank character
 * from linebuf, reading in a new line if linebuf 
 * is exhausted.
 */
static char getNextCahr(void) 
{
	if (!(linepos < bufsize)){
		if(fgets(linebuf, BUFLEN - 1, stdin)){
			bufsize = strlen(linebuf);
			linepos = 0;
			return linebuf[linepos++];
		}
		else
			return EOF;
	}
	else
		return linebuf[linepos++];
}

/*
 * ungetNextCar backtracks one character in linebuf
 */
static void ungetNextCar(void)
{
	linepos--; 
}

/*
 * The main function of scanner.
 * function getToken returns the next token in  
 * source file
 */
TokenType getToken(void)
{

}
