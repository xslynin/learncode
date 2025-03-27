#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#define FILE 	"/dev/test"

int main(){
	int fd = -1;

	fd = open(FILE, O_RDWR);
	if(fd<0){
		printf("open %s error\n", FILE);
		exit(1);
	}
	printf("open %s success.\n", FILE);
	write(fd,"on",2);
	sleep(2);
	write(fd,"off",3);
	close(fd);
	return 0;
}
