#include <linux/kernel.h>   /* printk() */
#include <linux/module.h>
#include <linux/fs.h>       /* everything... */
#include <linux/errno.h>    /* error codes */
#include <linux/types.h>    /* size_t */
#include <asm/uaccess.h>    /* copy_from_user */

#include "osex.h"

int osex_major = 239;
int sum = 0;

struct file_operations osex_fops = {
    .owner = THIS_MODULE,
    .read  = osex_read,
    .write = osex_write,
    .ioctl = osex_ioctl,
};

ssize_t 
osex_read(struct file *filep, char *buf, size_t size, loff_t *off)
{
    char kbuf[30];
    unsigned long left;
    int len;

    sprintf(kbuf, "%d\n", sum);
    len = strlen(kbuf) + 1;
    if (*off >= len){
        return 0;
    }

    left = copy_to_user(buf, kbuf, len);
    if (left){
        return -EFAULT;
    }
    *off += len;
    return len;

}
    
ssize_t 
osex_write(struct file *filep, const char *buf, size_t size, loff_t *off)
{
    char kbuf[11];
    int  v;
    unsigned long left;

    kbuf[10] = '\0'; /* for safety */
    
    if (size > 10){
        return -EINVAL;
    }

    left = copy_from_user(kbuf, buf, size);
    if (left){
        return -EFAULT;
    }
    
    sscanf(kbuf, "%d", &v);
    sum += v;
    return size;
}


int 
osex_ioctl(struct inode *inode, struct file *filep, 
               unsigned int cmd, unsigned long arg)
{
    switch(cmd){
    case OSEX_IOC_RESET:
        sum = 0;
        return 0;
    case OSEX_IOC_SET:
        sum = arg;
        return 0;
    default:
        return -EINVAL;
    }
}

int
osex_init_module(void)
{
    int result;
    result = register_chrdev(osex_major, "osex", &osex_fops);
    if (result < 0) {
        printk(KERN_WARNING "osex: regist fail\n");
        return result;
    }
    return 0;
}

void
osex_clear_module(void)
{
    unregister_chrdev(osex_major, "osex");
}

module_init(osex_init_module);
module_exit(osex_clear_module);
