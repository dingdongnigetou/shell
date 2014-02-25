/*
 * (C) 2014 HuangJinDong
 *
 * src/exec.c
 *
 * separate it from main.c to make main.c simply, 
 * it fork a new process and execute it.
 * 
 */

#include "exec.h"
#include "globals.h"
#include "errorprocess.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

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

	/* error process */
	error_process();

	/* waiting for child to exit */
	if ((pid == waitpid(pid, &status, 0)) < 0)
		fprintf(stderr, "waitpid error...");
}

