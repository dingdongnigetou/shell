/*
 * src/build_in.c
 *
 * (C) 2014 HuangJinDong
 *
 */

#include "globals.h"
#include "build_in.h"
#include <string.h>
#include <unistd.h>
#include <errno.h>

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
		case NO:/* nothing */
		default:break;	
	}
}

void do_cd()
{
	/* change to the arg[1] always */
	if (arg[1][0] != 0){
		if (!chdir(arg[1]))
			strcpy(pwd, arg[1]); /* update the current work director */
		else{
			/* error process, errno define at src/main.c */
			if (errno == ENOENT){
				fprintf(stdout, "ddsh: cd: %s: No such file or directory\n", arg[1]);
				errno = 0; /* resume */
			}
			else if (errno == ENOTDIR){
				fprintf(stdout, "ddsh: cd: %s: Not a directory\n", arg[1]);
				errno = 0;
			}
		}
	}
}

void do_exit()
{
	fprintf(stdout, "exit\n");
}

void do_pwd()
{
	fprintf(stdout, "%s\n", pwd);
}

void do_history()
{
	fprintf(stdout, "history\n");
}

