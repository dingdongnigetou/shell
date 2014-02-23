#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int
main (void)
{
	int ch;
	struct termios old_term;
	struct termios cur_term;
	int ret;
	tcgetattr (STDIN_FILENO, &old_term);
	memcpy (&cur_term, &old_term, sizeof (cur_term));
	cur_term.c_lflag &= ~(ICANON);
	cur_term.c_cc[VMIN] = 1;
	cur_term.c_cc[VTIME] = 0;
	ret = tcsetattr (STDIN_FILENO, TCSANOW, &cur_term);
	if (ret < 0)
	  {
		  printf ("Can't set\n");
		  return 1;
	  }

	while(1){
		ch = getchar();
		if (ch == 65){
			FILE *fp = fopen(".history", "r");
			char buf[256];
			fgets(buf, 256, fp);
			printf("%s", buf);
		}
	}

	tcsetattr (STDIN_FILENO, TCSANOW, &old_term);
	return 0;

}
