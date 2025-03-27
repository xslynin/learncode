#include <sys/stat.h>
#include <fcntl.h>
#include <linux/input.h>
#include <stdio.h>
#include <string.h>

int main(){
	int fd, ret;
	struct input_event ev;
	fd = open("/dev/input/event2", O_RDONLY);
	if(fd < 0){
		printf("open the button input device failed!\n");
		goto err;
	}

	while(1){
		memset(&ev, 0, sizeof(struct input_event));
		ret = read(fd, &ev, sizeof(struct input_event));
		if(ret < 0){
			perror("read");
			goto err;
		}
		printf("----------\n");
		printf("type : %hd \ncode : %hd\nvalue : %d\n", ev.type, ev.code, ev.value);
		printf("----------\n");
	}
	close(fd);
	return 0;

err:
	return -1;
}
