/*
 * src/keyprocess.c
 *
 * (C) 2014 HuangJingDong
 *
 * deal with some keys
 *
 */

#include "keyprocess.h"
#include <termios.h>
#include <unistd.h>
#include <string.h>

int keyprocess()
{
	int ch;
	int ret;
	struct termios old_term;
	struct termios cur_term;

	tcgetattr (STDIN_FILENO, &old_term);
	memcpy (&cur_term, &old_term, sizeof (cur_term));
	cur_term.c_lflag &= ~(ICANON);
	cur_term.c_cc[VMIN] = 1;
	cur_term.c_cc[VTIME] = 0;
	ret = tcsetattr (STDIN_FILENO, TCSANOW, &cur_term);

	if (ret < 0)
		printf ("Can't set\n");
        while (1){
		ch = getchar();
		switch(ch)
			{
			case 65:fprintf(stdout,"up\n");
				break;
			case 66:fprintf(stdout,"down\n");
				break;
			case 68:fprintf(stdout, "left\n");
				break;
			case 67:fprintf(stdout, "right\n");
				break;
			default:
				break;
		}
	}
	/* resume the old terminal sets */
	tcsetattr (STDIN_FILENO, TCSANOW, &old_term);

	return ch;
}

