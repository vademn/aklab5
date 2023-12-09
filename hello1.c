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


struct my_struct {
	struct list_head list_node;     // Linked list node
	ktime_t timestamp;		// ktime_t field
};

// Declare a static variable for the head of the list
static LIST_HEAD(my_list_head);

int print_hello(unsigned int count)
{

	int k;
	struct my_struct *entry;

	//Print the string based on the number_of_hellos value
	pr_info("Number_of_hellos: %u\n", count);

	if (count == 0 || (count > 5 && count <= 10)) {
		pr_warn("Warning: hello_number is set to %u, which is a bit shaky.\n", count);
	} else if (count > 10) {
		pr_err("Error: number_of_hellos is too large. Module is not loaded.\n");
		BUG_ON(1);
	}

	for (k = 1; k <= count; k++) {

		// Simulate kmalloc() returning 0 for 7 element
		if (k == 7) {
			entry = NULL;
		} else {
			entry = kmalloc(sizeof(struct my_struct), GFP_KERNEL);
		}

		if (!entry) {
			pr_err("Error allocating memory for my_struct.\n");
			return -ENOMEM;
		}

		INIT_LIST_HEAD(&entry->list_node);
		entry->timestamp = ktime_get();// Set the timestamp

		// Add entry to the linked list
		list_add_tail(&entry->list_node, &my_list_head);
	
		// Print Hello, world! and Event time
		pr_info("Hello, World!(from Kravchenko Vadym) Event time in nanoseconds: %lld ns\n", ktime_to_ns(entry->timestamp));
	}

	return 0;
}
EXPORT_SYMBOL(print_hello);

void exit_hello(void)
{
	struct my_struct *entry, *tmp;

	// Iterate through the list
	list_for_each_entry_safe(entry, tmp, &my_list_head, list_node) {

		// Print Event time in nanoseconds
		pr_info("BYE! Event time in nanoseconds: %lld ns\n", ktime_to_ns(entry->timestamp));

		// Remove the entry from the list
		list_del(&entry->list_node);

		// Free the allocated memory
		kfree(entry);
	}
}
EXPORT_SYMBOL(exit_hello);
