#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "osex.h"

int main(int argc, char *argv[])
{
    int fd;
    int value;

    if (argc != 2){
        fprintf(stderr, "error\n");
        return 1;
    }

    value = atoi(argv[1]);

    fd = open("/dev/ex", O_WRONLY);
    if (fd < 0){
        perror("osex ctrl");
        return 1;
    }

    if (ioctl(fd, OSEX_IOC_SET, value)){
        perror("osex ctrl");
        return 1;
    }
    return 0;
}
