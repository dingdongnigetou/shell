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

/* from scan.h */
char tokenString[MAXTOKENLEN + 1];
char arg[MAXTOKENLEN + 1][MAXTOKENLEN + 1];

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

	while (1){
		token = getToken();

		switch(token)
		{
		case COMMAND:
			fprintf(stdout, "command\n");
			break;
		case PARAM:
			fprintf(stdout, *arg);
			fprintf(stdout, "\n");
			break;
		case ENDINPUT:	
			/* if stdin then wait for inputing from user */
			if (INPUT == STDIN)
				fprintf(stdout, "ddsh%% "); 
			/* else end program */
			else
				goto END;
			break;
		default:
			fprintf(stdout, "error...");
			break;
		}
	}
		
END:	return 0;
}

