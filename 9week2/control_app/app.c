#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/sysmacros.h>

#define LED_MAJOR_NUMBER 502
#define LED_MINOR_NUMBER 100
#define BUTTON_MAJOR_NUMBER 503
#define BUTTON_MINOR_NUMBER 101
#define LED_DEV_PATH_NAME "/dev/led_misson"
#define BUTTON_DEV_PATH_NAME "/dev/button_misson"
#define LED_STATUS_OFF 0
#define LED_STATUS_ON 1
#define INTERVAL 500

#define IOCTL_MAGIC_NUMBER	'j'
#define IOCTL_CMD_SET_DIRECTION		_IOWR(IOCTL_MAGIC_NUMBER, 0, int)
#define IOCTL_CMD_SET_LED_ON		_IOWR(IOCTL_MAGIC_NUMBER, 1, int)
#define IOCTL_CMD_SET_LED_OFF		_IOWR(IOCTL_MAGIC_NUMBER, 2, int)


int main(void){
	dev_t led_dev, button_dev;
	int led, button;
	int pin_direction;
	led_dev = makedev(LED_MAJOR_NUMBER,LED_MINOR_NUMBER);
	button_dev = makedev(BUTTON_MAJOR_NUMBER,BUTTON_MINOR_NUMBER);
	mknod(LED_DEV_PATH_NAME, S_IFCHR|0666, led_dev);
	mknod(BUTTON_DEV_PATH_NAME, S_IFCHR|0666, button_dev);

	led = open(LED_DEV_PATH_NAME, O_RDWR);
	button = open(BUTTON_DEV_PATH_NAME, O_RDWR);
	
	if(led < 0){
		printf("fail to open led\n");
		return -1;
	}
	if(button < 0){
		printf("fail to open button\n");
		return -1;
	}
	
	pin_direction = 1;
	ioctl(led, IOCTL_CMD_SET_DIRECTION, &pin_direction);
	
	int led_status = LED_STATUS_OFF;
	int current_button_value = 0, prev_button_value = 0;
	
	while(1){
		usleep(INTERVAL);
		prev_button_value = current_button_value;
		// read button value	
		read(button, &current_button_value, sizeof(int));
		// if button value change, then riging edge detect
		if(prev_button_value == 0 && current_button_value != 0){
			if(led_status == LED_STATUS_ON){
				ioctl(led, IOCTL_CMD_SET_LED_OFF);
				led_status = LED_STATUS_OFF;
			}else{
				ioctl(led, IOCTL_CMD_SET_LED_ON);
				led_status = LED_STATUS_ON;
			}
		}			
	}
	
	close(button);
	close(led);
	
	return 0;
}

