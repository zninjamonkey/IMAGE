#include <unistd.h>
#include <string.h>
#include <linux/uinput.h>
#include <fcntl.h>  
#include <stdio.h>

int fd;

struct GamepadStatus
{
   int btnA;
   int btnB;
   int btnY;
   int btnX;

   int btnSel;
   int btnSta;
   int btnMen;

   int rBump;
   int lBump;

   float rTrig;
   int rBtn;
   float lTrig;
   int lBtn;

   int rSBtn;
   int lSBtn;

   float rStkX;
   float rStkY;
   float lStkX;
   float lStkY;

   int rDP;
   int lDP;
   int uDP;
   int dDp;
};

void emit(int fd, int type, int code, int val)
{
   struct input_event ie;

   ie.type = type;
   ie.code = code;
   ie.value = val;
   /* timestamp values below are ignored */
   ie.time.tv_sec = 0;
   ie.time.tv_usec = 0;

   write(fd, &ie, sizeof(ie));
}


// this stuff will be done with sdl
// void inputEventRecieved()
// {
   
// }

// void updateInput(struct GampadStatus state)
// {

// }

void applyInputState(struct GamepadStatus state)
{
   emit(fd, EV_KEY, BTN_SOUTH, state.btnA);
   emit(fd, EV_SYN, SYN_REPORT, 0);
   emit(fd, EV_KEY, BTN_EAST, state.btnB);
   emit(fd, EV_SYN, SYN_REPORT, 0);
   emit(fd, EV_KEY, BTN_NORTH, state.btnY);
   emit(fd, EV_SYN, SYN_REPORT, 0);
   emit(fd, EV_KEY, BTN_WEST, state.btnX);
   emit(fd, EV_SYN, SYN_REPORT, 0);
   emit(fd, EV_KEY, BTN_TL2, state.lBump);
   emit(fd, EV_SYN, SYN_REPORT, 0);
   emit(fd, EV_KEY, BTN_TR2, state.rBump);
   emit(fd, EV_SYN, SYN_REPORT, 0);
   emit(fd, EV_KEY, BTN_THUMBR, state.rSBtn);
   emit(fd, EV_SYN, SYN_REPORT, 0);
   emit(fd, EV_KEY, BTN_THUMBL, state.lSBtn);
   emit(fd, EV_SYN, SYN_REPORT, 0);
   emit(fd, EV_KEY, BTN_SELECT, state.btnSel);
   emit(fd, EV_SYN, SYN_REPORT, 0);
   emit(fd, EV_KEY, BTN_START, state.btnSta);
   emit(fd, EV_SYN, SYN_REPORT, 0);
   emit(fd, EV_KEY, BTN_MODE, state.btnMen);
   emit(fd, EV_SYN, SYN_REPORT, 0);
   emit(fd, EV_KEY, BTN_DPAD_DOWN, state.dDp);
   emit(fd, EV_SYN, SYN_REPORT, 0);
   emit(fd, EV_KEY, BTN_DPAD_LEFT, state.lDP);
   emit(fd, EV_SYN, SYN_REPORT, 0);
   emit(fd, EV_KEY, BTN_DPAD_RIGHT, state.rDP);
   emit(fd, EV_SYN, SYN_REPORT, 0);
   emit(fd, EV_KEY, BTN_DPAD_UP, state.uDP);
   emit(fd, EV_SYN, SYN_REPORT, 0);

   // printf("lstkx: %f\n", state.lStkX);
   emit(fd, EV_ABS, ABS_X, (int)state.lStkX);
   emit(fd, EV_SYN, SYN_REPORT, 0);
   emit(fd, EV_ABS, ABS_Y, (int)state.lStkY);
   emit(fd, EV_SYN, SYN_REPORT, 0);
   emit(fd, EV_ABS, ABS_RX, (int)state.rStkX);
   emit(fd, EV_SYN, SYN_REPORT, 0);
   emit(fd, EV_ABS, ABS_RY, (int)state.rStkY);
   emit(fd, EV_SYN, SYN_REPORT, 0);
   emit(fd, EV_ABS, ABS_HAT1X, (int)state.rTrig);
   emit(fd, EV_SYN, SYN_REPORT, 0);
   emit(fd, EV_ABS, ABS_HAT1Y, (int)state.lTrig);
   emit(fd, EV_SYN, SYN_REPORT, 0);

}

void createDevice()
{
   fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);

   int btn_codes[] = 
   {
   BTN_SOUTH,      //A
   BTN_EAST,      //B
   BTN_NORTH,      //Y
   BTN_WEST,      //X
   BTN_THUMBL,      //LS Btn
   BTN_THUMBR,      //RS Btn
   BTN_DPAD_UP, 
   BTN_DPAD_DOWN,
   BTN_DPAD_LEFT,
   BTN_DPAD_RIGHT,
   BTN_SELECT,
   BTN_START,
   BTN_MODE,
   BTN_TR,      //Binary RTrigger
   BTN_TL,      //Binary LTrigger
   BTN_TR2,      //Binary Lower RTrigger
   BTN_TL2,      //Binary Lower LTrigger
   };

   int axis_codes[] = 
   {
   ABS_HAT1X,      //Analog RTrigger
   ABS_HAT1Y,      //Analog LTrigger
   ABS_HAT2X,      //Analog Lower RTrigger
   ABS_HAT2Y,      //Analog Lower LTrigger
   ABS_X,      //LS X
   ABS_Y,      //LS Y
   ABS_RX,     //RS X
   ABS_RY     //RS Y
   };


   ioctl(fd, UI_SET_EVBIT, EV_KEY);
   ioctl(fd, UI_SET_EVBIT, EV_ABS);
   for (int i = 0; i < sizeof(btn_codes) / sizeof(btn_codes[0]); i++){
      ioctl(fd, UI_SET_KEYBIT, btn_codes[i]);
   }

   for (int i = 0; i < sizeof(axis_codes) / sizeof(axis_codes[0]); i++){
      ioctl(fd, UI_SET_ABSBIT, axis_codes[i]);
   }

   struct uinput_setup usetup;
   struct uinput_abs_setup uabs_setup_lx;
   struct uinput_abs_setup uabs_setup_ly;
   struct uinput_abs_setup uabs_setup_rx;
   struct uinput_abs_setup uabs_setup_ry;
   struct uinput_abs_setup uabs_setup_trigr;
   struct uinput_abs_setup uabs_setup_trigl;

   struct input_absinfo absinfo;

   memset(&usetup, 0, sizeof(usetup));
   usetup.id.bustype = BUS_USB;
   usetup.id.vendor = 0x1234; /* sample vendor */
   usetup.id.product = 0x5678; /* sample product */
   strcpy(usetup.name, "Generic Virtual Gamepad");

   memset(&uabs_setup_lx, 0, sizeof(uabs_setup_lx));
   memset(&absinfo, 0, sizeof(absinfo));
   absinfo.minimum = -32767;
   absinfo.maximum = 32767;
   // absxinfo.resolution

   uabs_setup_lx.absinfo = absinfo;
   uabs_setup_lx.code = ABS_X;

   uabs_setup_ly.absinfo = absinfo;
   uabs_setup_ly.code = ABS_Y;

   uabs_setup_rx.absinfo = absinfo;
   uabs_setup_rx.code = ABS_RX;

   uabs_setup_ry.absinfo = absinfo;
   uabs_setup_ry.code = ABS_RY;

   uabs_setup_trigl.absinfo = absinfo;
   uabs_setup_trigl.code = ABS_HAT1Y;

   uabs_setup_trigr.absinfo = absinfo;
   uabs_setup_trigr.code = ABS_HAT1X;

   ioctl(fd, UI_DEV_SETUP, &usetup);

   ioctl(fd, UI_ABS_SETUP, &uabs_setup_lx);
   ioctl(fd, UI_ABS_SETUP, &uabs_setup_ly);
   ioctl(fd, UI_ABS_SETUP, &uabs_setup_rx);
   ioctl(fd, UI_ABS_SETUP, &uabs_setup_ry);
   ioctl(fd, UI_ABS_SETUP, &uabs_setup_trigl);
   ioctl(fd, UI_ABS_SETUP, &uabs_setup_trigr);

   ioctl(fd, UI_DEV_CREATE);

   struct GamepadStatus gPadState;
   

   /*
    * On UI_DEV_CREATE the kernel will create the device node for this
    * device. We are inserting a pause here so that userspace has time
    * to detect, initialize the new device, and can start listening to
    * the event, otherwise it will not notice the event we are about
    * to send. This pause is only needed in our example code!
    */
   usleep(200 * 1000);
}

void cleanUp() {
   sleep(1);
   ioctl(fd, UI_DEV_DESTROY);
   close(fd);
}

// int main(void)
// {


   /* Key press, report the event, send key release, and report again */
   // emit(fd, EV_KEY, KEY_TOUCHPAD_TOGGLE, 1);
   // emit(fd, EV_SYN, SYN_REPORT, 0);
   // emit(fd, EV_KEY, KEY_TOUCHPAD_TOGGLE, 0);
   // emit(fd, EV_SYN, SYN_REPORT, 0);

   // emit(fd, EV_KEY, KEY_TOUCHPAD_TOGGLE, 1);
   // emit(fd, EV_SYN, SYN_REPORT, 0);
   // emit(fd, EV_KEY, KEY_TOUCHPAD_TOGGLE, 0);
   // emit(fd, EV_SYN, SYN_REPORT, 0);

   // for(int i = 0; i < 20; i++){
   //    emit(fd, EV_KEY, BTN_SOUTH, 1);
   //    emit(fd, EV_SYN, SYN_REPORT, 0);
   //    sleep(1);
   //    emit(fd, EV_KEY, BTN_SOUTH, 0);
   //    emit(fd, EV_SYN, SYN_REPORT, 0);
   //    sleep(1);
   // }

   /*
    * Give userspace some time to read the events before we destroy the
    * device with UI_DEV_DESTOY.
    */
   // return 0;
// }
