#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/ktime.h>
#include <linux/slab.h>
#include <linux/list.h>
#include "hello1.h"

MODULE_AUTHOR("Dima");
MODULE_DESCRIPTION("Hello1 module with simulated kmalloc error");
MODULE_LICENSE("Dual BSD/GPL");

static LIST_HEAD(hello_list);
static int alloc_counter = 0; // Лічильник викликів для симуляції помилки

// Реалізація функції print_hello
void print_hello(void)
{
	struct hello_entry *entry;

	// Виділення пам’яті для нового запису
	entry = kmalloc(sizeof(*entry), GFP_KERNEL);

	// Симуляція помилки після 5-го виклику
	alloc_counter++;
	if (alloc_counter == 5) {
		entry = NULL; // Примусово задаємо NULL, імітуючи помилку kmalloc()
	}

	// Використання entry без перевірки
	entry->time_before = ktime_get(); // Тут виникне помилка, якщо entry == NULL
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
