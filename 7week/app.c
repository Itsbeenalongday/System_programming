#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char ** argv){
	int dev;
	char buffer[1024];
	char input[100];
	printf("Input the number\n");
	scanf("%s",input);

	dev = open("/dev/sysprog_device", O_RDWR);
	
	if(dev == -1){
		perror("failed to open; because ");
		return 1;
	}
	
	//printf("dev = %d\n",dev);
	
	write(dev, input, strlen(input));
	read(dev, buffer, strlen(input));
	
	printf("Read from Device : %s\n", buffer);
	
	close(dev);
	
	exit(EXIT_SUCCESS);
}
