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

/* from scan.h */
char tokenString[MAXTOKENLEN + 1];
char const arg[MAXTOKENLEN + 1][MAXTOKENLEN + 1];
char getNextChar(void);
void ungetNextChar(void);

/* global variables */
FILE *source;
int  INPUT;

int main(int argc, char *argv[])
{
	TokenType token;
	pid_t     pid;
	int       status; /* child process's status */
	
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

	while (getNextChar() != EOF){
		token = getToken();
		char *arg1[] = {"ls", "-a", "-l", "/usr", (char *)0};

		switch(token)
		{
		case COMMAND:
			fprintf(stdout, "%s\n", tokenString);
			break;
		case PARAM:
			break;
		case ENDINPUT:	
			if ((pid = fork()) < 0)
				fprintf(stderr, "fork error...");
			else if (pid == 0)
				execvp("ls", arg);
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

