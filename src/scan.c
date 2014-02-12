/*
 * (C) 2014 HuangJinDong
 *
 * src/scan.c
 *
 * The scanner implementmtion of the ddsh.
 *
 */

#include "globals.h"
#include "scan.h"
#include <string.h>

/* states in scanner DFA */
typedef enum{
	/* will be add more */
	START, INCOMMAND, INPARAM, INCOMMENT, DONE
}StateType;

/* the length of the input buffer for source code lines */
#define BUFLEN 256

/* global varibale */
TokenType   lastToken;       

static char linebuf[BUFLEN]; /* holds the current line */
static int  linepos = 0;     /* current position in linebuf */
static int  bufsize = 0;     /* current size of buffer string */
char        tokenString[MAXTOKENLEN + 1]; /* extern form scan.h */
char const  arg[MAXTOKENLEN + 1][MAXTOKENLEN + 1];

char getNextChar(void) 
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

void ungetNextChar(void)
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
	int argrow = 0;           /* for arg row */

	/* for parameter tempator */
	char temp[MAXTOKENLEN + 1];
	int  templen = 0; 

	while (state != DONE){
		char ch = getNextChar();
		save    = TRUE;
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
				lastToken    = ENDINPUT;
			}
			/* end of file  */
			else if (INPUT == AFILE && ch == EOF ){
				save  = FALSE;
				state = DONE;
				currentToken = ENDINPUT;
				lastToken    = ENDINPUT;
			}
			/* not end until EOF */
			else if (INPUT == AFILE && ch == '\n')
				save  = FALSE;
			else if (lastToken == COMMAND){
				save  = FALSE;
				state = INPARAM;
				strcpy(arg[argrow++], tokenString); /* the begin of parameters */
				temp[templen++] = ch;               /* collect parameters */
			}
		        else 		
				state = INCOMMAND; /* all of other are command*/
			break;
		case INCOMMAND:
			/* teminal characters */
			if (ch == ' ' || ch == '\t' || ch == ';' || ch == '&' || 
					ch == '|' || ch == ')' || ch == ')'){
				save  = FALSE;	
				state = DONE;
				currentToken = COMMAND;
				lastToken    = COMMAND;
			}
			else if (ch == '\n'){
				state        = DONE;
				save         = FALSE;
				currentToken = COMMAND;
				lastToken    = COMMAND;
				ungetNextChar();	/* return to START */
                        }
			break;
		case INPARAM:
			if (ch == ';' || ch == '&' || ch == '|' || ch == '(' || ch == ')'){
				state        = DONE;
				currentToken = PARAM;
				lastToken    = PARAM;

				temp[0] = (char *)0;
				temp[1] = '\0';
				strcpy(arg[argrow++], temp); /* the end of parameters */
			}	
			else if (ch == '\n'){
				state        = DONE;
				save         = FALSE;
				currentToken = PARAM;
				lastToken    = PARAM;
				ungetNextChar();

				temp[templen] = '\0';
				templen       = 0;
				strcpy(arg[argrow++], temp);

				temp[0] = (char *)0;
				temp[1] = '\0';
				strcpy(arg[argrow++], temp); /* the end of parameters */
			}
			else if (ch == ' ' || ch == '\t'){
				/* collect parameters into arg[][] */
				temp[templen]   = '\0';
				templen         = 0;
				strcpy(arg[argrow++], temp);
			}
			else
				temp[templen++] = ch;
			save = FALSE; /* parameters save to arg array, not to tokenString */
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
