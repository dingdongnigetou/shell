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

/* prototypes */
static void stmt_sequence();
static void statement();
static void if_stmt();
static void while_stmt();
static void exp();

static void match(TokenType expected)
{
	if (token == expected)
		token = getToken();
	else
		fprintf(stderr, "unexpected token: %s\n", tokenString);
}

void stmt_sequence()
{
	statement();
	while (token != ENDFILE){
		match(SEMI);
		statement();
	}
}

void statement()
{
	switch(token)
	{

	}
}

void parse()
{

}

