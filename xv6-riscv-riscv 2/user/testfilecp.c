#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"

int
main(void)
{
    int fd;
    char buf[16];

    fd = open("a", O_CREATE | O_RDWR);
    if(fd < 0){
        printf("open failed\n");
        exit(1);
    }

    write(fd, "ABC", 3);

    if(checkpoint(0) == 0){
        write(fd, "DEF", 3);
        restore(0);
    }

    write(fd, "XYZ", 3);

    close(fd);

    fd = open("a", O_RDONLY);

    int n = read(fd, buf, sizeof(buf)-1);
    buf[n] = 0;

    printf("file = %s\n", buf);

    close(fd);

    exit(0);
}