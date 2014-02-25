/*
 * src/readprocess.c
 *
 * (C) 2014 HuangJingDong
 *
 * deal with some keys
 *
 */

#include "globals.h"
#include "readprocess.h"
#include <string.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

/* for read buf */
static char *line_read = (char *)0;

char *rl_gets()
{
	if (line_read){
		free(line_read);
		line_read = (char *)0;
	}

	line_read = readline("[dingdong ]# ");

	if (line_read && *line_read)
		add_history(line_read); /* add command to history */
	return line_read;
}

