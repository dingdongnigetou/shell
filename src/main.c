/*
 * 2014 (C) HuangJinDong 
 *
 * main.c
 *
 */

#include "globals.h"

/* global variables */
FILE *source;
int  INPUT;

int main(int argc, char *argv[])
{
	TokenType token;
	
	/* no file then wait for inputing from stdin */
	if (argc == 1){
		INPUT  = STDIN;
		source = stdin; 
	}
	/* else from AFILE */
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
			printf("COMMAND\n");
			break;
		case PARAM:
			printf("PARAM\n");
			break;
		}
		if (token == ENDINPUT)
			break;
	}
		
	return 0;
}

