import evdev
import evdev.ecodes as codes

import csv

import virtual_gamepad


input_definitions_csv = open('./input-definitions.csv', 'r')
reader = csv.reader(input_definitions_csv)
input_definitions = list(reader)
print(input_definitions)

device = evdev.InputDevice('/dev/input/event6')
print(device)

# device /dev/input/event1, name "USB Keyboard", phys "usb-0000:00:12.1-2/input0"

def handle_input(event):
    global input_definitions

    if event.type == codes.EV_KEY or event.type == codes.EV_ABS:
        # print(event.code)
        # print("done")

        # if event.code == 1:
        #     print(event.value)

        if event.code == int(input_definitions[0][1]):
            virtual_gamepad.set_button_state(codes.BTN_SOUTH, event.value)
            print("A button pressed")
        elif event.code == int(input_definitions[1][1]):
            virtual_gamepad.set_button_state(codes.BTN_EAST, event.value)
            print("B button pressed")
        elif event.code == int(input_definitions[2][1]):
            virtual_gamepad.set_button_state(codes.BTN_WEST, event.value)
            print("X button pressed")
        elif event.code == int(input_definitions[3][1]):
            virtual_gamepad.set_button_state(codes.BTN_NORTH, event.value)
            print("Y button pressed")
        elif event.code == int(input_definitions[4][1]):
            virtual_gamepad.set_button_state(codes.BTN_TR, event.value)
            print("right bumper pressed")
        elif event.code == int(input_definitions[5][1]):
            virtual_gamepad.set_button_state(codes.BTN_TL, event.value)
            print("left bumper pressed")

        # elif event.code == int(input_definitions[3][1]):
        #     print("Y button pressed")
        # elif event.code == int(input_definitions[3][1]):
        #     print("Y button pressed")
        # elif event.code == int(input_definitions[3][1]):
        #     print("Y button pressed")
        # elif event.code == int(input_definitions[3][1]):
        #     print("Y button pressed")

        elif event.code == int(input_definitions[15][1]):
            # print("dude common")
            virtual_gamepad.set_axis_state(codes.ABS_X, event.value)
        elif event.code == int(input_definitions[16][1]):
            virtual_gamepad.set_axis_state(codes.ABS_Y, event.value)


for event in device.read_loop():

    handle_input(event)
    # if event.type == evdev.ecodes.EV_KEY:
    #     print(evdev.categorize(event))
    # if event.type == evdev.ecodes.EV_ABS:
    #     print()