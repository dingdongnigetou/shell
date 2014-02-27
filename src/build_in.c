/*
 * src/build_in.c
 *
 * (C) 2014 HuangJinDong
 *
 */

#include "globals.h"
#include "build_in.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

/* which build in command, NO -> not build in */
typedef enum{
	NO, CD, PWD, EXIT, HISTORY 
}BuildInCommand;

/* toggle current directory */
void do_cd();

/* display current directory */
void do_pwd();

/* exit current shell with exit number */
void do_exit();

/* read .history which contains historical commands */
void do_history();

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
			/* error process */
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
	exit(atoi(arg[1])); /* exit number from arg[1] */
}

void do_pwd()
{
	fprintf(stdout, "%s\n", pwd);
}

void do_history()
{
	int  row = 1; /* line number */
	char temp[MAXTOKENLEN + 1];
	FILE *history = fopen(".history", "r");
	while (fgets(temp, MAXTOKENLEN + 1, history) != NULL){
		fprintf(stdout, "%d %s", row, temp);
		row++;
	}
	fclose(history);
}

