#include <linux/input.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>  
// #include <linux/joystick.h>

struct js_event {
        __u32 time;     /* event timestamp in milliseconds */
        __s16 value;    /* value */
        __u8 type;      /* event type */
        __u8 number;    /* axis/button number */
};

void main()
{
    int fd = open("/dev/input/js0", O_RDONLY);
    struct js_event e;

    while (1)
    {
        read(fd, &e, sizeof(e));
        printf("number: %d\n",e.number);
        printf("value: %d\n",e.value);
        printf("time: %d\n",e.time);
        printf("type: %d\n",e.type);
        usleep(20*1000);
    }
}