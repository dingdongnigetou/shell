#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

static char *line_read = (char *)0;

char *rl_gets()
{
	if (line_read){
		free(line_read);
		line_read = (char *)0;
	}
	line_read = readline("Please Enter: ");

	if (line_read && *line_read)
		add_history(line_read);
	return line_read;
}

int main()
{
	stifle_history(1000);
	char *mline;
	char buf[256];
	while(1){
		mline = rl_gets();

		printf("--%C", *(mline + 3));
	}
	return 0;
}
