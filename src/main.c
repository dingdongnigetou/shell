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
#include <string.h>
#include <errno.h>
#include <sys/wait.h>

/* global variables */
FILE  *source;
int   INPUT;
int   HAVEPARAM = FALSE; /* have parameter or not */
int   HAVECOM   = FALSE; /* have command or not */

/* fork a new process */
void  forktoexec();

int main(int argc, char *argv[])
{
	TokenType token;
	
	/* no file then wait for inputing from stdin */
	if (argc == 1){
		INPUT  = STDIN;
		source = stdin; 
		fprintf(stdout, "[:)]# ");
	}
	/* else from file */
	else{
		INPUT  = AFILE;
		source = fopen(argv[1], "r");
		if (source == NULL){
	//		fprintf(stderr, "File %s not found\n", argv[1]);
			exit(1);
		}
	}

	while (token != ENDINPUT){
		token     = getToken();
				
		switch(token)
		{
		case COMMAND:
			HAVECOM = TRUE;
			break;
		case PARAM:
			HAVEPARAM = TRUE;
			break;
		case ENDINPUT:	
			break;
		case NEWLINE:
			if (HAVECOM)
				forktoexec();
			fprintf(stdout, "[:)]# ");
			break;
		default:
			fprintf(stderr, "error...");
			break;
		}

	}
		
	exit(0);
}

void forktoexec()
{
	pid_t     pid;
	int       status;            /* child process's status */
	int       errno;             /* from errno.h to finger out the error */
	char      *temp[] = {"ls", "-a", "/usr", "0", "0", NULL};

	/* fork a child to execute a program */	
	if ((pid = fork()) < 0)
		fprintf(stderr, "fork error...");
	else if (pid == 0){
		if (HAVEPARAM)
			execvp(tokenString, arg);
		else
			execlp(tokenString, tokenString, (char *)0);
	}
	/* only consider this error for simply */
	if (errno == 2)
		fprintf(stdout, "ddsh: %s: command not found\n", tokenString);
	/* waitting for child to exit */
	if ((pid == waitpid(pid, &status, 0)) < 0)
		fprintf(stderr, "waitpid error...");
	/* resume */
	HAVEPARAM = FALSE;
	HAVECOM   = FALSE;
	for (int i = 0; i < MAXTOKENLEN + 1; i++)
		memset(arg + i, 0, MAXTOKENLEN + 1);
	memset(tokenString, 0, MAXTOKENLEN);
}

