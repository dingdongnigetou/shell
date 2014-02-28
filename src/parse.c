/*
 * (C) 2014 HuangJinDong
 *
 * src/parse.c
 *
 * The parser implementation for the ddsh.
 *
 */

#include "globals.h"
#include "scan.h"
#include "parse.h"

/* fill the arg[][] with 0 */
#define CLRARG                                \
for (int i = 0; i <= MAXTOKENLEN; i++)        \
	memset(arg + i, 0, MAXTOKENLEN + 1);

/* globals variables */
char  tokenString[MAXTOKENLEN + 1];
char  arg[MAXTOKENLEN + 1][MAXTOKENLEN + 1];

static TokenType token;        /* holds current token */

void parse()
{

}
