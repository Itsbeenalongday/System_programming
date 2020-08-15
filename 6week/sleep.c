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
#define GPCLR 0x28

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
	// output mode
	gpio[GPFSEL1/4] |= (1 << 8);
	// 1 sec loop
	volatile int i  = 0;
	
	while(i<5){
		gpio[GPSET0/4] |= (1 << 18);
		
		sleep(1);
		
		gpio[GPCLR/4] |= (1 << 18);
		
		sleep(1);
		
		i++;
	}
		
	munmap(gpio_memory_map, 4096);
}
