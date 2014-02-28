/*
 * (C) 2014 HuangJinDong 
 *
 * src/main.c
 *
 */

#include "globals.h"
#include "readprocess.h"
#include "parse.h"
#include "scan.h"
#include <stdlib.h>
#include <unistd.h>

/* global variables */
FILE  *source;
int   INPUT;
char  pwd[MAXTOKENLEN + 1];

char  tokenString[MAXTOKENLEN + 1];
char  arg[MAXTOKENLEN + 1][MAXTOKENLEN + 1];

int main(int argc, char *argv[])
{
	getcwd(pwd, MAXTOKENLEN + 1);      /* get current work director */
	initialize_readline();             /* readline initialization */
		
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

	/* begin to parse */
	parse();
		
	exit(0);
}

