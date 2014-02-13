/*
 * (C) 2014 HuangJinDong 
 *
 * src/main.c
 *
 */

#include "globals.h"
#include "scan.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

/* global variables */
FILE  *source;
int   INPUT;

/* from scan.h */
char  tokenString[MAXTOKENLEN + 1];
char* arg[MAXTOKENLEN + 1];

int main(int argc, char *argv[])
{
	TokenType token;
	pid_t     pid;
	int       status;    /* child process's status */
	int       HAVEPARAM; /* have parameter or not */
	
	/* no file then wait for inputing from stdin */
	if (argc == 1){
		INPUT  = STDIN;
		source = stdin; 
		fprintf(stdout, "ddsh%% ");
	}
	/* else from file */
	else{
		INPUT  = AFILE;
		source = fopen(argv[1], "r");
		if (source == NULL){
			fprintf(stderr, "File %s not found\n", argv[1]);
			exit(1);
		}
	}

	char* a[125];
	char  *temp={"ls"};
	a[0] = temp;
	a[1] = "-al";
	a[2] = "/usr";
	a[3] = 0;
	
	while (token != ENDINPUT){
		HAVEPARAM = FALSE;
		token     = getToken();
				
		switch(token)
		{
		case COMMAND:
			fprintf(stdout, "%s\n", tokenString);
			break;
		case PARAM:
			HAVEPARAM = TRUE;
			break;
		case ENDINPUT:	
			break;
		case NEWLINE:
			fprintf(stdout, "%s\n", tokenString);
			
			if ((pid = fork()) < 0)
				fprintf(stderr, "fork error...");
			else if (pid == 0){
				if (HAVEPARAM)
					execvp("ls", arg);
				else
					execlp(tokenString, tokenString, (char *)0);
			}

			if ((pid == waitpid(pid, &status, 0)) < 0)
				fprintf(stderr, "waitpid error...");

			/* clear arg array */
			for (int i = 0; i < MAXTOKENLEN; i++)
				memset(arg + i, '\0', MAXTOKENLEN);

			fprintf(stdout, "ddsh%% ");
			break;
		default:
			fprintf(stdout, "error...");
			break;
		}

	}
		
	exit(0);
}

