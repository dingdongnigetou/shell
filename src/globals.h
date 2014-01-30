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

typedef enum{
	/* key words */

	/* multicharacter words */
	ID, NUM,
	/* special symbols */
        ASSIGN, SEMI, PIPE, DAEMON, OR, AND, NEWLINE, LPAREN, RPAREN
}TokenType;


#endif /* _GLOBALS_H_ */

