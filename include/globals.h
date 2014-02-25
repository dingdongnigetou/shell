/*
 * (C) 2014 HuangJinDong
 *
 * include/globals.h
 *
 * global types and vars for ddsh.
 *
 */

#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>

/* for INPUT  */
#define STDIN 0
#define AFILE 1

#define TRUE  1
#define FALSE 0

/* the maximum size of a token */
#define MAXTOKENLEN 1024 

typedef enum{
	/* key words */

	/* multi character words */
	ID, NUM,
	/* special symbols */
        ASSIGN, SEMI, PIPE, DAEMON, OR, AND, RPAREM, LPAREN, NEWLINE,
	ENDINPUT, COMMAND, ERROR, PARAM 
}TokenType;

extern char  tokenString[MAXTOKENLEN + 1];          /* tokenString array stores the lexeme of each token */
extern char  arg[MAXTOKENLEN + 1][MAXTOKENLEN + 1]; /* command's parameters */
extern char  pwd[MAXTOKENLEN + 1];                  /* present work director */

extern FILE       *source;    /* file to be inputed, maybe it is a file or stdin. */
extern int        INPUT;      /* indicate the input is file or stdin */
extern TokenType  lastToken;  /* record the last token what is it */

#endif /* _GLOBALS_H_ */

