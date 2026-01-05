gcc -c -o ./build/joysticktest.o ./source/joystick-events.c 

gcc -c -o ./build/virtpad.o ./source/virtual-gamepad.c

gcc -o ./build/image ./build/virtpad.o ./build/joysticktest.o \
 -I./external/SDL/include/SDL3 -L./external/SDL/build \
 -lSDL3 \
 -Wl,-rpath,'$ORIGIN/lib' \
\

