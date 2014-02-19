/*
 * src/build_in.c
 *
 * (C) 2014 HuangJinDong
 *
 */

#include "build_in.h"
#include <string.h>

int isbuildin(char *command)
{
	BuildInCommand buildin = NO;

	if(!strcmp(command, "cd"))
		buildin = CD;
	else if (!strcmp(command, "pwd"))
		buildin = PWD;
	else if (!strcmp(command, "exit"))
		buildin = EXIT;
	else if (!strcmp(command, "history"))
		buildin = HISTORY;

	return buildin;
}

void runbuildin(int buildin)
{
	switch(buildin)
	{
		case CD:
			do_cd();
			break;
		case PWD:
			do_pwd();
			break;
		case EXIT:
			do_exit();
			break;
		case HISTORY:
			do_history();
			break;
		case NO:break; /* nothing */
		default:break;	
	}
}

void do_cd()
{
	fprintf(stdout, "cd\n");
}

void do_exit()
{
	fprintf(stdout, "exit\n");
}

void do_pwd()
{
	fprintf(stdout, "pwd\n");
}

void do_history()
{
	fprintf(stdout, "history\n");
}

