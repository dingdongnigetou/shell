/*
 * (C) 2014 HuangJinDong
 *
 * src/scan.c
 *
 * The scanner implementation of the ddsh.
 *
 */

#include "globals.h"
#include "scan.h"
#include "keyprocess.h"
#include <string.h>
#include <stdlib.h>

/* the length of the input buffer for source code lines */
#define BUFLEN 1024

/* states in scanner DFA */
typedef enum{
	/* will be add more */
	START, INCOMMAND, INPARAM, INCOMMENT, DONE
}StateType;

/* global variable */
TokenType   lastToken;       

static char linebuf[BUFLEN]; /* holds the current line */
static int  linepos = 0;     /* current position in linebuf */
static int  bufsize = 0;     /* current size of buffer string */

/* from scan.h */
char getNextChar(void) 
{
	if (!(linepos < bufsize)){
		if(fgets(linebuf, BUFLEN - 1, source)){
			/* record every command from stdin */
			if (INPUT == STDIN){
				FILE *history = fopen(".history", "a"); 
				fputs(linebuf, history);
				fflush(history); /* flush for write data to file */
				fclose(history);
			}
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

/* from scan.h */
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
	int argrow = 1;           /* for arg row */

	/* for parameter tempter */
	char temp[MAXTOKENLEN + 1];
	int  templen = 0; 
	
	while (state != DONE){
		char nextch;
		char ch = getNextChar();

		keyprocess(ch);

		save    = TRUE;
		switch (state)
		{
		case START:
			if (ch == '#')
				state = INCOMMENT;
			else if (ch == ' ' || ch == '\t')
				save = FALSE; /* still in START*/
			else if (ch == '\n'){
				save         = FALSE;
				state        = DONE;
				currentToken = NEWLINE;
				lastToken    = NEWLINE;
			}
			else if (ch == EOF ){
				save         = FALSE;
				state        = DONE;
				currentToken = ENDINPUT;
				lastToken    = ENDINPUT;
			}
		        else{ 		
				/* parameters */
				if (lastToken == COMMAND){
					save         = FALSE;
					state        = INPARAM;
					strcpy(arg[0], tokenString); /* the begin of parameters */
					ungetNextChar();
				}
				/* command */
				else
					state = INCOMMAND; /* all of other are command */
			}
			break;
		case INCOMMAND:
			/* terminal characters */
			if (ch == ' ' || ch == '\t' || ch == ';' || ch == '&' || 
					ch == '|' || ch == ')' || ch == ')' || ch == '\n'){
				save  = FALSE;	
				state = DONE;
				currentToken = COMMAND;
				lastToken    = COMMAND;

				if (ch == '\n')
					ungetNextChar(); /* return to START */
			}
			break;
		case INPARAM:
			/* terminal characters */
			if (ch == ';' || ch == '&' || ch == '|' || 
					ch == '(' || ch == ')' || ch == '\n'){
				state         = DONE;
				currentToken  = PARAM;
				lastToken     = PARAM;
				/* the end of parameters */
				if (templen != 0){
					temp[templen] = '\0';
					templen       = 0;
					strcpy(arg[argrow++], temp);
				}
				strcpy(arg[argrow], "#"); /* end character -> # */

				if (ch == '\n')
					ungetNextChar(); /* return to START */
			}	
			else if (ch == ' ' || ch == '\t'){
				/* ignore all ' ' and '\t' */
				nextch = getNextChar();
				while(nextch == ' ' || nextch == '\t')
					nextch = getNextChar();
				ungetNextChar();

				/* collect parameters into arg[][]  */
				temp[templen]   = '\0';
				templen         = 0;
				strcpy(arg[argrow++], temp);
			}
			else
				temp[templen++] = ch;
			save = FALSE; /* not save to tokenString */
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
		/* currently just save command */
		if (state == DONE && currentToken == COMMAND)
			tokenString[tokenStringIndex] = '\0';
		
	} /* while */	

	return currentToken;
}
