#define OSEX_IOC_MAGIC   'f'
#define OSEX_IOC_RESET   _IO(OSEX_IOC_MAGIC, 0)
#define OSEX_IOC_SET     _IO(OSEX_IOC_MAGIC, 1)

#ifdef __KERNEL__
ssize_t osex_read(struct file *, char *, size_t, loff_t *);
ssize_t osex_write(struct file *, const char *, size_t, loff_t *);
int osex_ioctl(struct inode *, struct file *, unsigned int, unsigned long);
#endif
