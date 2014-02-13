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

/* the maximum size of a token */
#define MAXTOKENLEN 256

typedef enum{
	/* key words */

	/* multicharacter words */
	ID, NUM,
	/* special symbols */
        ASSIGN, SEMI, PIPE, DAEMON, OR, AND, NEWLINE, LPAREN, RPAREN,
	ENDINPUT, COMMAND, ERROR, PARAM 
}TokenType;

extern FILE *source;  /* file to be inputed, maybe it is a file or stdin. */

extern int  INPUT;    /* indicate the input is file or stdin */

extern TokenType  lastToken;  /* record the last token what is it */

#endif /* _GLOBALS_H_ */

