/*
 * (C) 2014 HuangJinDong 
 *
 * src/main.c
 *
 */

#include "globals.h"
#include "scan.h"
#include "build_in.h"
#include "exec.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

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

int main(int argc, char *argv[])
{
	TokenType token;

	CLRARG                             /* for initialization */
	getcwd(pwd, MAXTOKENLEN + 1);      /* get current work director */
		
	/* no file then wait for inputing from stdin */
	if (argc == 1){
		INPUT  = STDIN;
		source = stdin; 
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
			break;
		case ENDINPUT:	
			break;
		default:
			fprintf(stderr, "error...\n");
			break;
		}
	}
		
	exit(0);
}


