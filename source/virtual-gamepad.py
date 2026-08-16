import time

import evdev
import evdev.ecodes as codes

events = {
    codes.EV_KEY : [codes.BTN_SOUTH, codes.BTN_EAST, codes.BTN_WEST, codes.BTN_NORTH]
}

uinput = evdev.UInput(events, "IMAGE Virtual Gamepad")

uinput.write(codes.EV_KEY, codes.BTN_SOUTH, 1)
uinput.syn()
time.sleep(10)
uinput.write(codes.EV_KEY, codes.BTN_SOUTH, 0)
uinput.syn()