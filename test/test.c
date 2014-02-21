#include <curses.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
	int ch;
	while(1){
		ch = getchar();
		if (ch == 27) fprintf(stdout, "ESC\n");
		if (ch == 224){
			ch = getchar();
			switch(ch)
			{
			case 72:fprintf(stdout,"up\n");
				break;
			case 80:fprintf(stdout,"down\n");
				break;
			case 75:fprintf(stdout, "left\n");
				break;
			case 77:fprintf(stdout, "right\n");
				break;
			default:
				break;
			}
		}
	}

	return 0;
}
