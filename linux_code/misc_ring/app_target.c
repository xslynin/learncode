#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>


#define MISC_FILE	"/dev/buzzer"
#define PWM_IOCTL_SET_FREQ		1
#define PWM_IOCTL_STOP			0


int main(){
	int fd, ret;
	printf("now lets try buzzer\n");
	
	fd = open(MISC_FILE, O_RDWR);
	if(fd < 0){
		error("misc buzzer device open");
	}
	
	if(ioctl(fd, PWM_IOCTL_SET_FREQ, 10000)){
		error("ioctl when set freq");
	}
	sleep(2);	
	if(ioctl(fd, PWM_IOCTL_STOP)){
		error("ioctl when stop");
	}

	close(fd);
	return 0;
}
