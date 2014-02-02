/*
 * 2014 (C) HuangJinDong
 *
 * globals.h
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

typedef enum{
	/* key words */

	/* multicharacter words */
	ID, NUM,
	/* special symbols */
        ASSIGN, SEMI, PIPE, DAEMON, OR, AND, NEWLINE, LPAREN, RPAREN,
	ENDOFFILE
}TokenType;

extern FILE* source; /* file to be inputed, maybe it is a file or stdin. */

extern int INPUT;    /* indicate the input is file or stdin */

#endif /* _GLOBALS_H_ */

