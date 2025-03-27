#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/fb.h>

#define FBDEVICE	"/dev/fb0"
#define WIDTH 		1024 
#define HEIGH 		800

struct fb_fix_screeninfo fix_info;
unsigned int * pbuf;	//locate certain pixel


//actually, the smem len include many other sfr 
void background_set(unsigned int width, unsigned int heigh, unsigned int color_argb){
	unsigned int i, j;
	for(i = 0; i < heigh ;i++){
		for(j = 0; j < width; j++){
			*(pbuf + i * WIDTH + j) = color_argb;
		}
	}
}

int main(int argc, char * argv[]){
	int fd, ret;

	fd = open(FBDEVICE, O_RDWR);
	if(fd < 0){
		perror("open fb device");
	}
	printf("open done!\n");

	//operate the fb
	ret = ioctl(fd, FBIOGET_FSCREENINFO, &fix_info);
	if(ret < 0){
		perror("ioctl");
		goto end;
	}
	
	printf("the start of memaddr is : 0x%x, the length is :%d\n", fix_info.smem_start, fix_info.smem_len);

	pbuf = mmap(NULL, fix_info.smem_len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(pbuf == NULL){
		perror("mmap");
		goto end;
	}
	printf("pbuf = %p\n", pbuf);
	background_set(WIDTH, HEIGH,(unsigned int)argv[1]);


mmap_end:
	munmap((void *)pbuf, fix_info.smem_len);

end:
	close(fd);
	return ret;
}
