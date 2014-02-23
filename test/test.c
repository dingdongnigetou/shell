#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	int ret, i;
	char c;
	fd_set readfd;
	struct timeval timeout;
	while(1){
		timeout.tv_sec = 0;
		timeout.tv_usec = 200;
		FD_ZERO(&readfd);
		FD_SET(0, &readfd);
		ret = select(0 + 1, &readfd, NULL, NULL, &timeout);
		if (FD_ISSET(0, &readfd)){
			i = read(0, &c, 1);
			if (c == '\n')
				continue;
			printf(":::%c\n", c);
			if (c == 'q')
				break;
		}
	}

	return 0;
}
