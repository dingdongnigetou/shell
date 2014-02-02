/*
 * 2014 (C) HuangJinDong
 *
 * scan.c
 *
 * The scanner implementmtion of the ddsh.
 *
 */

#include "globals.h"
#include "scan.h"

/* states in scanner DFA */
typedef enum{
	/* will be add more */
	START, INCOMMAND, INPARAM, INCOMMENT, DONE
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
static char getNextChar(void) 
{
	if (!(linepos < bufsize)){
		if(fgets(linebuf, BUFLEN - 1, source)){
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
	int tokenStringIndex = 0; /* index for storing into tokenString */
	TokenType currentToken;   /* current token to be returned */
	StateType state = START;  /* current state */
        bool save;                /* save tokenString or not */
	
	while (state != DONE){
		char ch = getNextChar();
		save = true;
		switch (state)
		{
		case START:
			if (ch == '#')
				state = INCOMMENT;
			else if (ch == ' ' || ch == '\t')
				save = false; /* still in START*/
			else if (ch == '\n')
				state = DONE;
		        else 		
				state = INCOMMAND; /* all of other are command*/

		case INCOMMAND:
			if (ch == ' ' || ch == '\t'){
				save = false;
				state = INPARAM;
			}
			else if (ch == '\n')
				state = DONE;
		
		}
	}	

}
