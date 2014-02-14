#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	
	char *arg[] = {"-a", "-l", "/usr"};
	char com[]  = "vv";
	int  ret;
	extern int errno;
	printf("%s\n", arg[2]);
	ret = execvp(com, arg);
	printf("errno == %d\n", errno);
	 
	return 0;
}
