/*
 * 2014 (C) HuangJinDong
 *
 * scan.h
 *
 * The scanner interface for ddsh.
 *
 */

#ifndef _SCAN_H_
#define _SCAN_H_

/* the maximum size of a token */
#define MAXTOKENLEN 40

/* tokenString array stores the lexeme of each token */
extern char tokenString[MAXTOKENLEN + 1];

/* function getToken returns the 
 * next token in source file 
 */
TokenType getToken(void);

#endif /* _SCAN_H_ */

