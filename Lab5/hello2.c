#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include "hello1.h"

MODULE_AUTHOR("Student");
MODULE_DESCRIPTION("Hello2 module");
MODULE_LICENSE("Dual BSD/GPL");

static uint repeats = 1;
module_param(repeats, uint, 0444);
MODULE_PARM_DESC(repeats, "Number of times to call print_hello");

static int __init hello2_init(void)
{
	uint i;

	if (repeats == 0 || (repeats >= 5 && repeats <= 10)) {
		pr_warn("Warning: repeats is %u, but continuing.\n", repeats);
	} else if (repeats > 10) {
		pr_err("Error: repeats > 10, exiting with -EINVAL.\n");
		return -EINVAL;
	}

	for (i = 0; i < repeats; i++) {
		print_hello();
	}

	return 0;
}

static void __exit hello2_exit(void)
{
	pr_info("Exiting hello2 module.\n");
}

module_init(hello2_init);
module_exit(hello2_exit);

