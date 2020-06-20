/*  
 *  hello.c - The simplest kernel module.
 */

#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <linux/kthread.h>

static struct task_struct *mythreads=NULL;

static int mythread_func(void *unused) {

	printk(KERN_INFO"mythread_func is called\n");
	return 0;
}

int init_module(void)
{

	printk(KERN_INFO"Creating my own thread\n");

	mythreads=kthread_run(mythread_func,NULL,"mythread");
	if (mythreads) {
		printk(KERN_INFO "Thread is created sucssfully\n");
	}
	else {
		printk(KERN_INFO "Unable to create a thread\n");
	}
	return 0;
}

void cleanup_module(void)
{
	if (mythreads) {
		kthread_stop(mythreads);
		printk(KERN_INFO "my thread is stop\n");
	}
	printk(KERN_INFO "Hello world module exit\n");
}
