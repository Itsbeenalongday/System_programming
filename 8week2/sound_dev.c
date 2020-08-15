#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/time.h>


#include <asm/mach/map.h>
#include <asm/io.h>
#include <asm/uaccess.h>

#define SOUND_MAJOR_NUMBER 501
#define SOUND_DEV_NAME "sound"

#define GPIO_BASE_ADDR 0x3F200000
#define GPFSEL1 0x04
#define GPSET0 0x1c
#define GPCLR0 0x28
#define GPLEV0 0x34

static void __iomem *gpio_base;
volatile unsigned int *gpsel1;
volatile unsigned int *gpset1;
volatile unsigned int *gpclr1;
volatile unsigned int *gplev0;

struct timeval start;
struct timeval end;
unsigned long duration;
unsigned int pin18 = 1 << 18;
unsigned int pin17 = 1 << 17;
unsigned int zero = 0;

int sound_open(struct inode *inode, struct file *filp){
	printk(KERN_ALERT "SOUND driver open!!\n");
	
	gpio_base = ioremap(GPIO_BASE_ADDR, 0x60);
	gpsel1 = (volatile unsigned int *)(gpio_base + GPFSEL1);
	gpset1 = (volatile unsigned int *)(gpio_base + GPSET0);
	gpclr1 = (volatile unsigned int *)(gpio_base + GPCLR0);
	gplev0 = (volatile unsigned int *)(gpio_base + GPLEV0);
	// 17 pin output mode
	*gpsel1 |= (1<<17);
	if(((*gpsel1) & pin17) == pin17){
		printk(KERN_ALERT "trigger output mode activation!!\n");
	}
	return 0;
}

int sound_release(struct inode *inode, struct file *filp){
	printk(KERN_ALERT "SOUND driver closed!!\n");
	iounmap((void *)gpio_base);
	return 0;
}

ssize_t sound_write(struct file *filp, const char *buf, size_t count, loff_t *f_pos){
	printk(KERN_ALERT "sound driver write function called\n");
	
	return count;
}

ssize_t sound_read(struct file *filp, char *buf, size_t count, loff_t *f_pos){
	start.tv_usec = 0;
	end.tv_usec = 0;
	printk(KERN_ALERT "SOUND read function called\n");
	printk(KERN_ALERT "trigger on!!\n");
	*gplev0 |= 0;
	*gpset1 |= (1<<17);
	udelay(10);
	printk(KERN_ALERT "trigger off!!\n");
	*gpclr1 |= (1<<17);
	printk(KERN_ALERT "ultra sonic start!!\n");
	// start
	printk(KERN_ALERT "start time : %ld\n", start.tv_usec);
	printk(KERN_ALERT "end time : %ld\n", end.tv_usec);
	do_gettimeofday(&start);
	printk(KERN_ALERT "start time : %ld\n", start.tv_usec);
	// for echo is not high 
	while(((*gplev0) & pin18) != pin18);
	// loop that if ehco is high then break
	// end time
	do_gettimeofday(&end);
	printk(KERN_ALERT "end time : %ld\n", end.tv_usec);

	printk(KERN_ALERT "ultra sonic arrived!!\n");
	// round trip time calculate (us)
	duration = (unsigned long)end.tv_usec - (unsigned long)start.tv_usec;
	// kernel double type makes insmod unknown symbol error 
	copy_to_user(buf,&duration,sizeof(duration));
	return count;
}

static struct file_operations sound_fops = {
	.owner = THIS_MODULE,
	.open = sound_open,
	.write = sound_write,
	.read = sound_read,
	.release = sound_release
};

int __init sound_init(void){
	if(register_chrdev(SOUND_MAJOR_NUMBER, SOUND_DEV_NAME, &sound_fops) < 0){
		printk(KERN_ALERT "SOUND driver initalization fail\n");
	}else{
		printk(KERN_ALERT "SOUND driver initalization success\n");
	}
	
	return 0;
}

void __exit sound_exit(void){
	unregister_chrdev(SOUND_MAJOR_NUMBER, SOUND_DEV_NAME);
	printk(KERN_ALERT "SOUND driver exit done!!\n");
}

module_init(sound_init);
module_exit(sound_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("You sung min");
MODULE_DESCRIPTION("sound");




