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
char  commands[MAXTOKENLEN + 1];
char  tokenString[MAXTOKENLEN + 1];
char  arg[MAXTOKENLEN + 1][MAXTOKENLEN + 1];

static TokenType token;              /* holds current token */
static char number[MAXTOKENLEN + 1]; /*  holds number in []*/

/* prototypes */
static void stmt_sequence();
static void statement();
static void if_stmt();
static void while_stmt();
static void do_command();

/* get all token when syntax error happened */
static void clearToken()
{
	while (token != NEWLINE)
		token = getToken();
}

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
		while(token != SEMI){
			token = getToken();
			if (token == NEWLINE)
				break;
		}
		do_command();
		break;
	case SEMI:
		match(SEMI);
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
	/*  if [ num ]; then dosometing; fi */
	match(IF);
	if (token != LPAREN){
		fprintf(stderr, "missing '[' behinds if\n");
		clearToken();
		return;
	}
	match(LPAREN);
	
	if (token != NUM){
		fprintf(stderr, "missing number in '[]'\n");
		clearToken();
		return;
	}
	else{
		match(NUM);
		strcpy(number, tokenString);
	}

	if (token != RPAREN){
		fprintf(stderr, "missing ']'\n");
		clearToken();
		return;
	}	
	match(RPAREN);

	if (token != SEMI){
		fprintf(stderr, "missing ';' behinds ']'\n");
		clearToken();
		return;
	}
	match(SEMI);

	if (token != THEN){
		fprintf(stderr, "missing 'then'\n");
		clearToken();
		return;
	}
	match(THEN);

	while(token != SEMI){
		token = getToken();
		if (token == NEWLINE)
			break;
	}

	if (token != SEMI){
		fprintf(stderr, "missing ';' behinds commands\n");
		clearToken();
		return;
	}
	match(SEMI);

	if (token != FI){
		fprintf(stderr, "missing 'fi' at the end\n");
		clearToken();
		return;
	}
	match(FI);

	if (atoi(number))
		do_command();
}

void while_stmt()
{
	/* while [ num ]; do dosomething; done */
	match(WHILE);
	if (token != LPAREN){
		fprintf(stderr, "missing '[' behinds while\n");
		clearToken();
		return;
	}
	match(LPAREN);

	if (token != NUM){
		fprintf(stderr, "missing number in '[]'\n");
		clearToken();
		return;
	}
	match(NUM);
	strcpy(number, tokenString);
	
	if (token != RPAREN){
		fprintf(stderr, "missing ']'\n");
		clearToken();
		return;
	}
	match(RPAREN);

	if (token != SEMI){
		fprintf(stderr, "missing ';' behinds ']'\n");
		clearToken();
		return;
	}
	match(SEMI);

	if (token != DO){
		fprintf(stderr, "missing 'do' behinds commands\n");
		clearToken();
		return;
	}
	match(DO);

	while(token != SEMI){
		token = getToken();
		if (token == NEWLINE)
			break;
	}

	if (token != SEMI){
		fprintf(stderr, "missing ';' behinds 'do'\n");
		clearToken();
		return;
	}
	match(SEMI);

	if (token != DONEWHILE){
		fprintf(stderr, "missing 'done' at the end\n");
		clearToken();
		return;
	}
	match(DONEWHILE);

	while(atoi(number))
		forktoexec();
}

void do_command()
{
	forktoexec();
	CLRARG;
}

void parse()
{
	token = getToken();
	stmt_sequence();
}

