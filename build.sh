gcc -o gamepadtest gamepad-polling.c -I./external/SDL/include/SDL3 -L./external/SDL/build -lSDL3 -Wl,-rpath,'$ORIGIN/lib'
mv gamepadtest ./build