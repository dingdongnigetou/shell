/*
 * (C) 2014 HuangJinDong
 *
 * include/scan.h
 *
 * The scanner interface for ddsh.
 *
 */

#ifndef _SCAN_H_
#define _SCAN_H_

/* the maximum size of a token */
#define MAXTOKENLEN 256

#define TRUE  1
#define FALSE 0

/* tokenString array stores the lexeme of each token */
extern char tokenString[MAXTOKENLEN + 1];

/* command's parameters */
extern char arg[MAXTOKENLEN + 1][MAXTOKENLEN + 1];

/* function getToken returns the 
 * next token in source file 
 */
TokenType getToken(void);

#endif /* _SCAN_H_ */

