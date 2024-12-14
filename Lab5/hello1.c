#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/ktime.h>
#include <linux/slab.h>
#include <linux/list.h>
#include "hello1.h"

MODULE_AUTHOR("Student");
MODULE_DESCRIPTION("Hello1 module");
MODULE_LICENSE("Dual BSD/GPL");

static LIST_HEAD(hello_list);

// Реалізація функції print_hello
void print_hello(void)
{
	struct hello_entry *entry;

	entry = kmalloc(sizeof(*entry), GFP_KERNEL);
	if (!entry) {
		pr_err("Failed to allocate memory for list entry.\n");
		return;
	}

	entry->time_before = ktime_get();
	pr_info("Hello, world!\n");
	entry->time_after = ktime_get();

	list_add_tail(&entry->list, &hello_list);
}
EXPORT_SYMBOL(print_hello);

// Функція завершення модуля
static void __exit hello1_exit(void)
{
	struct hello_entry *entry, *tmp;

	pr_info("Exiting hello1 module and printing times:\n");

	list_for_each_entry_safe(entry, tmp, &hello_list, list) {
		pr_info("Time taken: %lld ns\n",
			ktime_to_ns(ktime_sub(entry->time_after, entry->time_before)));
		list_del(&entry->list);
		kfree(entry);
	}
}

module_exit(hello1_exit);

