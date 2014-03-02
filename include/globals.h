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
	/* multi character words */
	ID, NUM,
	/* special symbols */
        ASSIGN, SEMI, PIPE, DAEMON, OR, AND, RPAREN, LPAREN, NEWLINE,
	ENDFILE, COMMAND, ERROR, PARAM, 
	/* key words */
	IF, THEN, ELSE, FI, WHILE, DO, DONEWHILE
}TokenType;

extern char  tokenString[MAXTOKENLEN + 1];
extern char  commands[MAXTOKENLEN + 1];             /* holds the commands */
extern char  arg[MAXTOKENLEN + 1][MAXTOKENLEN + 1]; /* command's parameters */
extern char  pwd[MAXTOKENLEN + 1];                  /* present work director */

extern FILE       *source;    /* file to be inputed, maybe it is a file or stdin. */
extern int        INPUT;      /* indicate the input is file or stdin */

#endif /* _GLOBALS_H_ */

