#ifndef VIRTUAL_GAMEPAD_H
#define VIRTUAL_GAMEPAD_H

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

void applyInputState(struct GamepadStatus state);

void createDevice();

void cleanUp();

#endif