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
}StateType;

/* the length of the input buffer for source code lines */
#define BUFLEN 256

static char linebuf[BUFLEN]; /* holds the current line */
static int  linepos = 0;     /* current position in linebuf */
static int  bufsize = 0;     /* current size of buffer string */
char        tokenString[MAXTOKENLEN + 1]; /* extern form scan.h */

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
        int save;                 /* save tokenString or not */
	
	while (state != DONE){
		char ch = getNextChar();
		save = TRUE;
		switch (state)
		{
		case START:
			if (ch == '#')
				state = INCOMMENT;
			else if (ch == ' ' || ch == '\t')
				save = FALSE; /* still in START*/
			/* end of stdin */
			else if (INPUT == STDIN && ch == '\n'){
				save  = FALSE;
				state = DONE;
				currentToken = ENDINPUT;
			}
			/* end of file  */
			else if (INPUT == AFILE && ch == EOF ){
				save  = FALSE;
				state = DONE;
				currentToken = ENDINPUT;
			}
			/* not end until EOF */
			else if (INPUT == AFILE && ch == '\n')
				save = FALSE;
			/* the begining of paramter */
			else if (ch == '-' || ch == '--'){
				save  = FALSE;
				state = INPARAM;
			}
		        else 		
				state = INCOMMAND; /* all of other are command*/
			break;
		case INCOMMAND:
			/* teminal characters */
			if (ch == ' ' || ch == '\t' || ch == ';' || ch == '&' || ch == '&&' || 
					ch == '||' || ch == '|' || ch == ')' || ch == ')'){
				save  = FALSE;	
				state = DONE;
				currentToken = COMMAND;
			}
			break;
		case INPARAM:
			/* terminal characters */
			if (ch == ' ' || ch == '\t' || ch == ';' || ch == '&' || ch == '&&' ||
					ch == '||' || ch == '|' || ch == ')' || ch == ')'){
				save  = FALSE;	
				state = DONE;
				currentToken = PARAM;
			}
			break;
		case INCOMMENT:
			save = FALSE;
			if (ch == '\n')
				state = START;
			break;
		default:
			state = DONE; 
			currentToken = ERROR;
			break;
		} /* switch */

		if (save && tokenStringIndex <= MAXTOKENLEN)
			tokenString[tokenStringIndex++] = ch;
		if (state == DONE){
			tokenString[tokenStringIndex] = '\0';
		}

	} /* while */	

	return currentToken;
}
