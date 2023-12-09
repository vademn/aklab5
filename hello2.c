#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/ktime.h>
#include "hello1.h"

MODULE_AUTHOR("Serhii Popovych <serhii.popovych@globallogic.com>, edited by Kravchenko Vadym IO-12");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training");
MODULE_LICENSE("Dual BSD/GPL");

// How many times the string should be printed
static unsigned int number_of_hellos = 7;
module_param(number_of_hellos, uint, 0644);
MODULE_PARM_DESC(number_of_hellos, "Number of times to print \"Hello, world!\"");


static int __init hello2_init(void)
{
	ktime_t before, after;

	before = ktime_get();

	print_hello(number_of_hellos);

	after = ktime_get();

	pr_info("Print duration in hello2: %lld ns\n", ktime_to_ns(ktime_sub(after, before)));

	return 0;
}

static void __exit hello2_exit(void)
{
	exit_hello();
}

module_init(hello2_init);
module_exit(hello2_exit);
