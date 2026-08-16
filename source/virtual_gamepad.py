import time

import evdev
import evdev.ecodes as codes

events = {
    codes.EV_KEY : [codes.BTN_SOUTH, 
                    codes.BTN_EAST, 
                    codes.BTN_WEST, 
                    codes.BTN_NORTH, 
                    codes.BTN_SELECT, 
                    codes.BTN_START, 
                    codes.BTN_MODE, 
                    codes.BTN_TL, 
                    codes.BTN_TR, 
                    codes.BTN_THUMBL, 
                    codes.BTN_THUMBR,
                    codes.BTN_DPAD_LEFT,
                    codes.BTN_DPAD_RIGHT,
                    codes.BTN_DPAD_UP,
                    codes.BTN_DPAD_DOWN],

    codes.EV_ABS : [(codes.ABS_X, evdev.AbsInfo(value=0, min=0, max=32767*2, fuzz=0, flat=0, resolution=0)),
                    (codes.ABS_Y, evdev.AbsInfo(value=0, min=0, max=32767*2, fuzz=0, flat=0, resolution=0)),
                    (codes.ABS_RX, evdev.AbsInfo(value=0, min=0, max=32767*2, fuzz=0, flat=0, resolution=0)),
                    (codes.ABS_RY, evdev.AbsInfo(value=0, min=0, max=32767*2, fuzz=0, flat=0, resolution=0)),
                    (codes.ABS_HAT1X, evdev.AbsInfo(value=0, min=0, max=1028, fuzz=0, flat=0, resolution=0)),
                    (codes.ABS_HAT1Y, evdev.AbsInfo(value=0, min=0, max=1028, fuzz=0, flat=0, resolution=0)),
                    (codes.ABS_HAT0X, evdev.AbsInfo(value=0, min=-1, max=1, fuzz=0, flat=0, resolution=0)),
                    (codes.ABS_HAT0Y, evdev.AbsInfo(value=0, min=-1, max=1, fuzz=0, flat=0, resolution=0))
                    ]
}

uinput = evdev.UInput(events, "IMAGE Virtual Gamepad")

def set_button_state(button, value):
    uinput.write(codes.EV_KEY, button, value)
    uinput.syn()

def set_axis_state(axis, value):
    uinput.write(codes.EV_ABS, axis, value)
    uinput.syn()
# uinput.write(codes.EV_KEY, codes.BTN_SOUTH, 1)
# uinput.syn()
# time.sleep(10)
# uinput.write(codes.EV_KEY, codes.BTN_SOUTH, 0)
# uinput.syn()