#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

#define GPIO_BASE_ADDR 0x3F200000
#define GPFSEL1 0x04
#define GPSET0 	0x1C
#define GPCLR0 0x28
#define GPFSEL2 0x08
#define GPLEV0 0x34


int main(){
	int fd = open("/dev/mem", O_RDWR|O_SYNC);
	if(fd < 0){
		printf("fail to open virtual memory\n");
		return -1;
	}
	
	char * gpio_memory_map = (char *)mmap(0, 4096, PROT_READ|PROT_WRITE, MAP_SHARED,fd,GPIO_BASE_ADDR);
	
	if(gpio_memory_map == MAP_FAILED)
	{
		printf("fail to mmap\n");
		return -1;
	}
	
	volatile unsigned int * gpio = (volatile unsigned int *)gpio_memory_map;
	

	
	unsigned int pin18 = 1 << 18;
	unsigned int pin20 = 1 << 20;
	unsigned int pin21 = 1 << 21;
	int flag1 =0, flag2 =0;
	int loop = 0;

START:
	gpio[GPSET0/4] |= pin21;
	printf("start\n");
	while(flag1 * flag2 != 1){
		if((gpio[GPLEV0/4] & pin20) == 0){
			flag1 = 1;
		}
		if((gpio[GPLEV0/4] & pin20) == pin20){
			flag2=1;
		}
	}
	flag1 =0, flag2 =0;
	printf("----------------------\n");
	loop ++;
	goto ONLOOP;

ONLOOP:
	printf("onloop\n");
	if(loop % 2 == 1) goto START;
	gpio[GPSET0/4] |= pin18;
	gpio[GPSET0/4] |= pin21;
	flag1 =0, flag2 =0;
	while(flag1 * flag2 != 1){
		if((gpio[GPLEV0/4] & pin20) == 0){
			flag1 = 1;
		}
		if((gpio[GPLEV0/4] & pin20) == pin20){
			flag2 = 1;
		}
	}
	flag1 =0, flag2 = 0;
	
	goto OFFLOOP;

OFFLOOP:
	gpio[GPCLR0/4] |= pin18;
	gpio[GPSET0/4] |= pin21;
	printf("offloop\n");
	flag1 =0, flag2 =0;
	//if(loop % 2 == 1) goto START;
	while(flag1 * flag2 != 1){
		if((gpio[GPLEV0/4] & pin20) == 0){
			flag1 = 1;
		}
		if((gpio[GPLEV0/4] & pin20) == pin20){
			flag2 = 1;
		}
	}
	flag1=0 , flag2 = 0;
	goto START;
	
	munmap(gpio_memory_map, 4096);
}
