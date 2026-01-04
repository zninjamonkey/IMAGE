#include <unistd.h>
#include <string.h>
#include <linux/uinput.h>
#include <fcntl.h>  

struct GampadStatus
{
   /* data */
   int btnA;
   int btnB;
   int btnY;
   int btnX;

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

void inputEventRecieved()
{
   
}

void updateInput(struct GampadStatus state)
{

}

void applyInput(int fd, struct GampadStatus state)
{
   emit(fd, EV_KEY, BTN_SOUTH, 1);
   emit(fd, EV_SYN, SYN_REPORT, 0);

}


void configureInputEvents(int uinputFile, int* eventCodes)
{
   ioctl(uinputFile, UI_SET_EVBIT, EV_KEY);
   ioctl(uinputFile, UI_SET_EVBIT, EV_ABS);
   for (int i = 0; i < sizeof(eventCodes) / sizeof(eventCodes[0]); i++){
      ioctl(uinputFile, UI_SET_KEYBIT, eventCodes[i]);
   }
}

int main(void)
{
   struct uinput_setup usetup;

   int fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);


   int codes[] = 
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
   BTN_TR,      //Binary RTrigger
   BTN_TL,      //Binary LTrigger
   BTN_TR2,      //Binary Lower RTrigger
   BTN_TL2,      //Binary Lower LTrigger
   ABS_HAT1X,      //Analog RTrigger
   ABS_HAT1Y,      //Analog LTrigger
   ABS_HAT2X,      //Analog Lower RTrigger
   ABS_HAT2Y,      //Analog Lower LTrigger
   ABS_X,      //LS X
   ABS_Y,      //LS Y
   ABS_RX,     //RS X
   ABS_RY     //RS Y
   };

   configureInputEvents(fd, codes);

   memset(&usetup, 0, sizeof(usetup));
   usetup.id.bustype = BUS_USB;
   usetup.id.vendor = 0x1234; /* sample vendor */
   usetup.id.product = 0x5678; /* sample product */
   strcpy(usetup.name, "Generic Virtual Gamepad");

   ioctl(fd, UI_DEV_SETUP, &usetup);
   ioctl(fd, UI_DEV_CREATE);

   struct GampadStatus gPadState;
   

   /*
    * On UI_DEV_CREATE the kernel will create the device node for this
    * device. We are inserting a pause here so that userspace has time
    * to detect, initialize the new device, and can start listening to
    * the event, otherwise it will not notice the event we are about
    * to send. This pause is only needed in our example code!
    */
//    sleep(1);
   usleep(200 * 1000);

   /* Key press, report the event, send key release, and report again */
   // emit(fd, EV_KEY, KEY_TOUCHPAD_TOGGLE, 1);
   // emit(fd, EV_SYN, SYN_REPORT, 0);
   // emit(fd, EV_KEY, KEY_TOUCHPAD_TOGGLE, 0);
   // emit(fd, EV_SYN, SYN_REPORT, 0);

   // emit(fd, EV_KEY, KEY_TOUCHPAD_TOGGLE, 1);
   // emit(fd, EV_SYN, SYN_REPORT, 0);
   // emit(fd, EV_KEY, KEY_TOUCHPAD_TOGGLE, 0);
   // emit(fd, EV_SYN, SYN_REPORT, 0);

   while (1){

      updateInputState(gPadState);

      applyInput(fd, gPadState);

      usleep(2 * 1000); //500hz polling
   }

   for(int i = 0; i < 20; i++){
      emit(fd, EV_KEY, BTN_SOUTH, 1);
      emit(fd, EV_SYN, SYN_REPORT, 0);
      sleep(1);
      emit(fd, EV_KEY, BTN_SOUTH, 0);
      emit(fd, EV_SYN, SYN_REPORT, 0);
      sleep(1);
   }
   /*
    * Give userspace some time to read the events before we destroy the
    * device with UI_DEV_DESTOY.
    */
   sleep(1);

   ioctl(fd, UI_DEV_DESTROY);
   close(fd);

   return 0;
}
