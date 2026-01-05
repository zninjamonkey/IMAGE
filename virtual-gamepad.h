#ifndef VIRTUAL_GAMEPAD_H
#define VIRTUAL_GAMEPAD_H

struct GampadStatus
{
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

void applyInputState(struct GampadStatus state);

void createDevice();

void cleanUp();

#endif