import evdev
import time

device = evdev.InputDevice('/dev/input/event6')
print(device)

path = device.phys + "-input-definitions.csv"

print("writing to " + path)

file = open("./" + path, "w")

used_codes = []

def get_next_key(name):
    waiting = True
    while waiting:
        time.sleep(0.1)
        for event in device.read_loop():
            if event.type == evdev.ecodes.EV_KEY and event.value == 1 and event.code not in used_codes:
                print("boo ya")
                file.write(name + "," + str(event.code) + "\n")
                used_codes.append(event.code)
                waiting = False
                break

def get_next_axis(name, bound):
    waiting = True
    while waiting:
        time.sleep(1)
        for event in device.read_loop():
            if (event.code in used_codes):
                continue
            if abs(event.value - 32767) < 5000:
                continue
            if event.type == evdev.ecodes.EV_ABS and abs(event.value) > bound :
                print("boo ya")
                file.write(name + "," + str(event.code) + "\n")
                used_codes.append(event.code)
                waiting = False
                break


# get_next_axis("dfs", 64000)
# get_next_axis("bru", 1000)
# get_next_axis("dude", 0.5)



print("press the A button")
get_next_key("A_BTN")

print("press the B button")
get_next_key("B_BTN")

print("press the X button")
get_next_key("X_BTN")

print("press the Y button")
get_next_key("Y_BTN")

print("press the right bumper")
get_next_key("R_BUMP")

print("press the left bumper")
get_next_key("L_BUMP")

print("press the right stick")
get_next_key("R_STICK")

print("press the left stick")
get_next_key("L_STICK")

print("press the start button")
get_next_key("START_BTN")

print("press the select button")
get_next_key("SELECT_BTN")

print("press the home button")
get_next_key("HOME_BTN")

print("press the right trigger")
get_next_axis("R_TRIG", 1000)

print("press the left trigger")
get_next_axis("L_TRIG", 1000)

print("push the right joystick right")
get_next_axis("R_X_STICK", 64000)

print("push the right joystick down")
get_next_axis("R_Y_STICK", 64000)

print("push the left joystick right")
get_next_axis("L_X_STICK", 64000)

print("push the left joystick down")
get_next_axis("L_Y_STICK", 64000)

print("press the right dpad arrow")
get_next_axis("X_PAD", 0.5)

print("press the down dpad arrow")
get_next_axis("Y_PAD", 0.5)
