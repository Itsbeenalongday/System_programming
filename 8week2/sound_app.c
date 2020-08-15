#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/sysmacros.h>

#define SOUND_MAJOR_NUMBER 501
#define SOUND_MIJOR_NUMBER 100
#define SOUND_DEV_PATH_NAME "/dev/ultrasonic"

int main(void){
	dev_t sound_dev;
	int fd;
	unsigned long d;
	
	sound_dev = makedev(SOUND_MAJOR_NUMBER,SOUND_MIJOR_NUMBER);
	mknod(SOUND_DEV_PATH_NAME, S_IFCHR|0666, sound_dev);
	
	fd = open(SOUND_DEV_PATH_NAME, O_RDWR);
	
	if(fd < 0){
		printf("fail to open file\n");
		return -1;
	}
	
	read(fd,&d,sizeof(d));
	long double distance;
	printf("round trip time: %lu us\n",d);
	distance = ((340*(long double)d)/10000)/2;
	printf("Distance measured by ultrasonic: %.18Lf cm\n",distance);
	close(fd);
	
	return 0;
}

