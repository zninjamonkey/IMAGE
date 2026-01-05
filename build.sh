gcc -o joysticktest joystick-events.c -I./external/SDL/include/SDL3 -L./external/SDL/build -lSDL3 -Wl,-rpath,'$ORIGIN/lib'
mv joysticktest ./build