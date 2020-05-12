#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	char buf[128];
	int fd = open(argv[1], O_RDONLY);
	if(fd == -1){
		perror("open");
		return -1;
	}
	
	int r = read(fd, buf, 128);
    write(1, buf, r);
	printf("\n");
	close(fd);
}



