#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/ktime.h>
#include <linux/slab.h>
#include <linux/list.h>

MODULE_AUTHOR("Serhii Popovych <serhii.popovych@globallogic.com>");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training");
MODULE_LICENSE("Dual BSD/GPL");

static uint repeats = 1; // Параметр із значенням за замовчанням
module_param(repeats, uint, 0444);
MODULE_PARM_DESC(repeats, "Number of times to print 'Hello, world!'");

// Структура для списку
struct hello_entry {
	struct list_head list;
	ktime_t time;
};

// Створення голови списку
static LIST_HEAD(hello_list);

static int __init hello_init(void)
{
	struct hello_entry *entry;
	uint i;

	// Обробка параметра repeats
	if (repeats == 0 || (repeats >= 5 && repeats <= 10)) {
		pr_warn("repeats is either 0 or in range 5-10. Proceeding with warning.\n");
	} else if (repeats > 10) {
		pr_err("repeats is greater than 10. Exiting with error.\n");
		return -EINVAL;
	}

	for (i = 0; i < repeats; i++) {
		entry = kmalloc(sizeof(*entry), GFP_KERNEL);
		if (!entry) {
			pr_err("Failed to allocate memory for list entry.\n");
			return -ENOMEM;
		}

		// Заносимо поточний час у структуру
		entry->time = ktime_get();
		list_add_tail(&entry->list, &hello_list);

		pr_info("Hello, world! %u\n", i + 1);
	}

	return 0;
}

static void __exit hello_exit(void)
{
	struct hello_entry *entry, *tmp;

	pr_info("Exiting module and printing times:\n");

	// Проходимося по списку
	list_for_each_entry_safe(entry, tmp, &hello_list, list) {
		pr_info("Time: %lld ns\n", ktime_to_ns(entry->time));
		list_del(&entry->list);
		kfree(entry);
	}
}

module_init(hello_init);
module_exit(hello_exit);

