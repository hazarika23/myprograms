#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include<linux/list.h>
#include<linux/slab.h>

struct list_head  mylist_head;
struct mydata {
      int key;
      struct list_head list;
      int count;
      int num;
};

int createalist(int count);
int destroylist(void);
struct kmem_cache *my_cacheptr=NULL;
int memory_pool_create(void)
{
	struct mydata mydata1;
	printk(KERN_INFO"Creating memory cache\n");
	INIT_LIST_HEAD(&mydata1.list);
	my_cacheptr=kmem_cache_create("my_cache", sizeof(struct mydata),
			0, SLAB_HWCACHE_ALIGN|SLAB_RECLAIM_ACCOUNT , NULL);
	if (my_cacheptr==NULL) {
		printk(KERN_INFO"Unable to create kmem cache\n");
	}
	return 0;
}

int memory_pool_destroy(void)
{
	if(my_cacheptr){
		printk(KERN_INFO"Destroying memory cache\n");
		(void) kmem_cache_destroy(my_cacheptr);
	}
	return 0;
}

int createalist(int count)
{
	int i;
	struct mydata *node;

	printk(KERN_INFO"Creating link list\n");
	for(i=0;i<count; i++) {
		node= (struct mydata *) kmem_cache_alloc(my_cacheptr, NR_KMALLOC_TYPES);
		node->key=i;
		node->count=0;
		node->num=1000+i;
		list_add(&node->list,&mylist_head);
	}

	return 0;
}


int destroylist(void) 
{
	static int count=0;
	struct mydata *entry;	
	list_for_each_entry(entry, &mylist_head, list) {
		count++;
		list_del(&entry->list);
	}
	printk(KERN_INFO"Total node free %d\n",count);
	return 0;
}

int init_module(void)
{
	INIT_LIST_HEAD(&mylist_head);
	memory_pool_create();
	createalist(100);
	printk(KERN_INFO "Hello world 1.\n");
	return 0;
}

void cleanup_module(void)
{
	destroylist();
	memory_pool_destroy();
	printk(KERN_INFO "Goodbye world 1.\n");
}

//module_init(init_module);
//module_exit(cleanup_module);
