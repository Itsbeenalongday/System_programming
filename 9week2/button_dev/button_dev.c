#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/time.h>
#include <linux/delay.h>

#include <asm/mach/map.h>
#include <asm/io.h>
#include <asm/uaccess.h>

#define BUTTON_DEV_NAME "button_misson"
#define BUTTON_MAJOR_NUMBER 503

#define GPIO_BASE_ADDR 0x3F200000
#define GPFSEL2 0x08
#define GPSET0 0x1c
#define GPCLR0 0x28
#define GPLEV0 0x34

static void __iomem *gpio_base;
volatile unsigned int *gpsel2;
volatile unsigned int *gpset1;
volatile unsigned int *gpclr1;
volatile unsigned int *gplev0;

unsigned int pin20 = 1 << 20;
unsigned int pin21 = 1 << 21;
unsigned int zero = 0;

int button_open(struct inode *inode, struct file *filp){
	printk(KERN_ALERT "button driver open!!\n");
	
	gpio_base = ioremap(GPIO_BASE_ADDR, 0x60);
	gpsel2 = (volatile unsigned int *)(gpio_base + GPFSEL2);
	gpset1 = (volatile unsigned int *)(gpio_base + GPSET0);
	gpclr1 = (volatile unsigned int *)(gpio_base + GPCLR0);
	gplev0 = (volatile unsigned int *)(gpio_base + GPLEV0);
	// 21 pin output mode
	*gpsel2 |= (1<<21);
	if(((*gpsel2) & pin21) == pin21){
		printk(KERN_ALERT "button 21 pin output mode activation!!\n");
	}
	// gpio write 21 1
	(*gpset1) |= pin21;
	
	return 0;
}

int button_release(struct inode *inode, struct file *filp){
	printk(KERN_ALERT "button driver closed!!\n");
	iounmap((void *)gpio_base);
	return 0;
}

ssize_t button_read(struct file *filp, char *buf, size_t count, loff_t *f_pos){
	// button 1 1 -> button pull
	unsigned int value = 0;
	if(((*gplev0) & pin20) == pin20){
		copy_to_user(buf,&value,sizeof(value));
	}else{ // button 0 0 -> button push
		value = 1;
		copy_to_user(buf,&value,sizeof(value));
		// gpio write 21 1
		(*gpset1) |= pin21;
		value = 0;
	}
	return count;
}

static struct file_operations button_fops = {
	.owner = THIS_MODULE,
	.open = button_open,
	.release = button_release,
	.read = button_read
};

int __init button_init(void){
	if(register_chrdev(BUTTON_MAJOR_NUMBER, BUTTON_DEV_NAME, &button_fops) < 0){
		printk(KERN_ALERT "button driver initalization fail\n");
	}else{
		printk(KERN_ALERT "button driver initalization success\n");
	}
	
	return 0;
}

void __exit button_exit(void){
	unregister_chrdev(BUTTON_MAJOR_NUMBER, BUTTON_DEV_NAME);
	printk(KERN_ALERT "button driver exit done!!\n");
}

module_init(button_init);
module_exit(button_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("You sung min");
MODULE_DESCRIPTION("button");




