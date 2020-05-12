#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	char buf[128] = {"this is a test"};
	int fd1 = mkfifo("123.txt", 0755);
	if(fd1 == -1){
		perror("fifo");
		return -1;
	}

	int fd = open(argv[1], O_WRONLY);
	if(fd == -1){
		perror("open");
		return -1;
	}

	write(fd, buf, strlen(buf));
	close(fd);
	return 0;
	
}
