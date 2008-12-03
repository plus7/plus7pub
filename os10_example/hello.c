#ifndef MODULE
#define MODULE
#endif

#include <linux/module.h>
#include <linux/kernel.h>

int
init_module(void)
{
    printk("<1>Hello World\n");
    return 0;
}

void
cleanup_module(void)
{
    printk("<1>Goodby\n");
}
