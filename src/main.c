/*
 * (C) 2014 HuangJinDong 
 *
 * src/main.c
 *
 */

#include "globals.h"
#include "scan.h"
#include "build_in.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>

/* fill the arg[][] with 0 */
#define CLRARG                                \
for (int i = 0; i <= MAXTOKENLEN; i++)        \
	memset(arg + i, 0, MAXTOKENLEN + 1);

/* global variables */
FILE  *source;
int   INPUT;
char  tokenString[MAXTOKENLEN + 1];
char  arg[MAXTOKENLEN + 1][MAXTOKENLEN + 1];
char  pwd[MAXTOKENLEN + 1];

int   HAVECOM   = FALSE; /* have command or not */
int   errno;             /* from errno.h to finger out the error */

/* fork a new process */
void  forktoexec();

int main(int argc, char *argv[])
{
	TokenType token;

	CLRARG                             /* for initialization */
	getcwd(pwd, MAXTOKENLEN + 1);      /* get current work director */
		
	/* no file then wait for inputing from stdin */
	if (argc == 1){
		INPUT  = STDIN;
		source = stdin; 
		fprintf(stdout, "[dingdong %s]# ", strrchr(pwd, '/') + 1);
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
	
	while (token != ENDINPUT){
		token     = getToken();
		switch(token)
		{
		case COMMAND:
			HAVECOM = TRUE;
			break;
		case PARAM:
			break;
		case NEWLINE:
			if (HAVECOM){
				if (isbuildin(tokenString))
					runbuildin(isbuildin(tokenString));
				else
					forktoexec();

				/* resume */
				HAVECOM = FALSE;
				CLRARG;
			}
			/* if exec command from a file then exit directly */
			if (INPUT == STDIN)
				fprintf(stdout, "[dingdong %s]# ", strrchr(pwd, '/') + 1);
			break;
		case ENDINPUT:	
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
	pid_t pid;
	int   i;                          /* index */
	int   status;                     /* child process's status */
	char  *arg_temp[MAXTOKENLEN + 1]; /* for arg array */

	/* fork a child to execute a program */	
	if ((pid = fork()) < 0)
		fprintf(stderr, "fork error...");
	else if (pid == 0){
		/* have parameter */
		if (arg[1][0] != 0){
			/*
			 * put the parameters which in arg into arg_temp 
			 * in order to set NULL to the end of parameters.
			 * this way maybe stupid, but it deals with the 
			 * problem that shit me few days.:-) 
			 *
			 */
			for (i = 0; strcmp(arg[i], "#") != 0; i++)
				arg_temp[i] = arg[i];
			arg_temp[i] = NULL;

			execvp(tokenString, arg_temp);
		}
		else{
			execlp(tokenString, tokenString, (char *)0);
		}
	}
	/* only consider this error for simply */
	if (errno == ENOENT){
		fprintf(stdout, "ddsh: %s: command not found\n", tokenString);
		errno = 0; /* resume */
	}
	/* waiting for child to exit */
	if ((pid == waitpid(pid, &status, 0)) < 0)
		fprintf(stderr, "waitpid error...");
}

