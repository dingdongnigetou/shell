#include <unistd.h>

int main(int argc, char *argv[])
{
	
	char *arg[] = {"ls", "-al", "/usr"};
	execvp("ls", arg);
	return 0;
}
