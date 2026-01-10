#include <linux/input.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>  
// #include <linux/joystick.h>

#include "virtual-gamepad.h"
#include "input-definitions.h"

#define JS_EVENT_BUTTON         0x01    /* button pressed/released */
#define JS_EVENT_AXIS           0x02    /* joystick moved */
#define JS_EVENT_INIT           0x80    /* initial state of device */

struct js_event {
        __u32 time;     /* event timestamp in milliseconds */
        __s16 value;    /* value */
        __u8 type;      /* event type */
        __u8 number;    /* axis/button number */
};

struct GamepadStatus gpad_state;

// void update_state()
// {
    
// }

void handle_event(struct js_event e)
{
    // e.type &= ~JS_EVENT_INIT
    // printf("%d\n", e.type);

    switch(e.type)
    {
        case JS_EVENT_INIT | JS_EVENT_BUTTON:

            // int subtype = JS_EVENT_BUTTON;
            printf("INIT BUTTON\n");
            switch(e.number)
            {
                case INP_A:
                    printf("initial A button: %d\n", e.value);
                    break;
                case INP_B:
                    printf("initial B button: %d\n", e.value);
                    break;
                case INP_X:
                    printf("initial X button: %d\n", e.value);
                    break;
                case INP_Y:
                    printf("initial Y button: %d\n", e.value);
                    break;
                case INP_RIGHT_BUMPER:
                    printf("initial right bumper: %d\n", e.value);
                    break;
                case INP_LEFT_BUMPER:
                    printf("initial left bumper: %d\n", e.value);
                    break;
                case INP_SELECT:
                    printf("initial select: %d\n", e.value);
                    break;
                case INP_START:
                    printf("initial start: %d\n", e.value);
                    break;
                case INP_MENU:
                    printf("initial MENU: %d\n", e.value);
                    break;
                case INP_RIGHT_STICK:
                    printf("initial RS: %d\n", e.value);
                    break;
                case INP_LEFT_STICK:
                    printf("initial LS: %d\n", e.value);
                    break;
            }
            break;
    
        case JS_EVENT_INIT | JS_EVENT_AXIS:
        
            // int subtype = JS_EVENT_AXIS;
            printf("INIT AXIS\n");
            switch(e.number)
            {
                case INP_LEFT_X_AXIS:
                    printf("initial left x: %d\n", e.value);
                    break;
                case INP_LEFT_Y_AXIS:
                    printf("initial left y: %d\n", e.value);
                    break;
                case INP_RIGHT_X_AXIS:
                    printf("initial right x: %d\n", e.value);
                    break;
                case INP_RIGHT_Y_AXIS:
                    printf("initial right y: %d\n", e.value);
                    break;
                case INP_RIGHT_TRIGGER:
                    printf("initial rt: %d\n", e.value);
                    break;
                case INP_LEFT_TRIGGER:
                    printf("initial lt: %d\n", e.value);
                    break;
                case INP_DPAD_X:
                    printf("initial dpx: %d\n", e.value);
                    break;
                case INP_DPAD_Y:
                    printf("initial dpy: %d\n", e.value);
                    break;
            }
            break;
    
        case JS_EVENT_BUTTON:

            printf("button: %d\n", e.number);
            break;

        case JS_EVENT_AXIS:
    
            printf("axis: %d\n", e.number);
            break;
    }
    
}

void main()
{
    int fd = open("/dev/input/js0", O_NONBLOCK);
    struct js_event e;

    while (1)
    {
        while(read(fd, &e, sizeof(e)) > 0) {
            handle_event(e);
        }
        // handle_event(e);
        // int wtffff = read(fd, &e, sizeof(e));

        // printf("read return value: %d\n", wtffff);
        // printf("number: %d\n",e.number);
        // printf("value: %d\n",e.value);
        // printf("time: %d\n",e.time);
        // printf("type: %d\n",e.type);
        usleep(1*1000);
    }
}