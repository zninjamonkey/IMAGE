import evdev

path = "new-input-definitions.h"

print("writing to " + path)

file = open("./" + path, "+a")

file.write("#ifndef INPUT_DEFINITIONS_H\n#define INPUT_DEFINITIONS_H\n")

print("press the A button")

device = evdev.InputDevice('/dev/input/event6')
print(device)
# device /dev/input/event1, name "USB Keyboard", phys "usb-0000:00:12.1-2/input0"

for event in device.read_loop():
    if event.type == evdev.ecodes.EV_KEY:
        print(evdev.categorize(event))


