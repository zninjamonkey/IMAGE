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
                    codes.BTN_TL2, 
                    codes.BTN_TR2, 
                    codes.BTN_THUMBL, 
                    codes.BTN_THUMBR,
                    codes.BTN_DPAD_LEFT,
                    codes.BTN_DPAD_RIGHT,
                    codes.BTN_DPAD_UP,
                    codes.BTN_DPAD_DOWN],

    codes.EV_ABS : [codes.ABS_X, 
                    codes.ABS_Y, 
                    codes.ABS_RX, 
                    codes.ABS_RY, 
                    codes.ABS_HAT1X, 
                    codes.ABS_HAT1Y]
}

uinput = evdev.UInput(events, "IMAGE Virtual Gamepad")

def set_button_state(button, value):
    uinput.write(codes.EV_KEY, button, value)
    uinput.syn()

# uinput.write(codes.EV_KEY, codes.BTN_SOUTH, 1)
# uinput.syn()
# time.sleep(10)
# uinput.write(codes.EV_KEY, codes.BTN_SOUTH, 0)
# uinput.syn()