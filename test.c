#include <unistd.h>

int main(int argc, char *argv[])
{
	
	char *arg[] = {"-a", "-l", "/usr"};
	char com[]  = "ls";
	printf("%s\n", arg[2]);
	execvp(com, arg);
	return 0;
}
