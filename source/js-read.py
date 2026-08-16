import evdev
import csv

import virtual-gamepad


input_definitions_csv = open('./input-definitions.csv', 'r')
reader = csv.reader(input_definitions_csv)
input_definitions = list(reader)
print(input_definitions)

device = evdev.InputDevice('/dev/input/event6')
print(device)

# device /dev/input/event1, name "USB Keyboard", phys "usb-0000:00:12.1-2/input0"

def handle_input(event):
    global input_definitions

    if event.type == evdev.ecodes.EV_KEY or event.type == evdev.ecodes.EV_ABS:
        # print(event.code)
        # print("done")

        # if event.code == 1:
        #     print(event.value)

        if event.code == int(input_definitions[0][1]):
            print("A button pressed")
        elif event.code == int(input_definitions[1][1]):
            print("B button pressed")
        elif event.code == int(input_definitions[2][1]):
            print("X button pressed")
        elif event.code == int(input_definitions[3][1]):
            print("Y button pressed")
        elif event.code == int(input_definitions[4][1]):
            print("right bumper pressed")
        elif event.code == int(input_definitions[5][1]):
            print("left bumper pressed")
        # elif event.code == int(input_definitions[3][1]):
        #     print("Y button pressed")
        # elif event.code == int(input_definitions[3][1]):
        #     print("Y button pressed")
        # elif event.code == int(input_definitions[3][1]):
        #     print("Y button pressed")
        # elif event.code == int(input_definitions[3][1]):
        #     print("Y button pressed")
        # elif event.code == int(input_definitions[3][1]):
        #     print("Y button pressed")
        # elif event.code == int(input_definitions[3][1]):
        #     print("Y button pressed")
        

for event in device.read_loop():

    handle_input(event)
    # if event.type == evdev.ecodes.EV_KEY:
    #     print(evdev.categorize(event))
    # if event.type == evdev.ecodes.EV_ABS:
    #     print()