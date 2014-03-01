/*
 * (C) 2014 HuangJinDong
 *
 * src/parse.c
 *
 * The parser implementation for the ddsh.
 *
 */

#include "globals.h"
#include "exec.h"
#include "scan.h"
#include "parse.h"
#include <string.h>
#include <stdlib.h>

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
static void do_command();

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
		if (token == SEMI)
			match(SEMI);
		statement();
	}
}

void statement()
{
	switch(token)
	{
	case IF: 
		if_stmt();
	       	break;
	case WHILE: 
		while_stmt();
	        break;
	case COMMAND: 
		do_command();
		break;
	case NEWLINE:
		match(NEWLINE);
		break;
	default: 
		fprintf(stderr, "unexpected token %s\n", tokenString);
		break;
	}
}

void if_stmt()
{
	/*  if [ num ]; then dosometing; else dootherthing; fi */
	match(IF);
	if (token == LPAREN){
		match(LPAREN);
		if (token == NUM){ 
			match(NUM);
			if (token == RPAREN){
				match(RPAREN);
				if (token == SEMI){
					match(SEMI);
					if (token == THEN){
						match(THEN);
						if (atoi(tokenString))
							stmt_sequence();
						else{
							if (token == ELSE)
								match(ELSE);
								stmt_sequence();
						}
					}
				}
			}
		}
	}

}

void while_stmt()
{
	/* while [ num ]; do dosomething; done */
	match(WHILE);
	match(LPAREN);
	match(NUM);
	match(RPAREN);
	match(SEMI);
	match(DO);
	if (atoi(tokenString))
		stmt_sequence();
	match(DONEWHILE);

}

void do_command()
{
	match(COMMAND);
	if (token == PARAM)
		match(PARAM);
        else if (token == SEMI)
		match(SEMI);
	else if (token == NEWLINE)
		match(NEWLINE);
	forktoexec();
	CLRARG;
}

void parse()
{
	token = getToken();
	stmt_sequence();
}

