#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/spinlock.h>

DEFINE_SPINLOCK(mysplock1);
spinlock_t mysplock2;

int init_module(void)
{
	printk(KERN_INFO "Hello world\n");

	spin_lock_init(&mysplock2);
	spin_lock(&mysplock1);

	spin_lock(&mysplock2);
	spin_unlock(&mysplock2);
	return 0;
}

void cleanup_module(void)
{
	printk(KERN_INFO "Goodbye world\n");
}


MODULE_LICENSE("GPL");
MODULE_AUTHOR("bikash.hazarika@gmail.com");
MODULE_DESCRIPTION("spinlock test");

