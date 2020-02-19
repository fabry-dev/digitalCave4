#ifndef POSITIONS_H
#define POSITIONS_H



static int buttonLedX[10]={250,133,15,133,250,513,630,748,630,513};
static int buttonLedY[10]={168,342,517,692,866,168,342,517,692,866};
static int buttonLedW[10]={196,196,196,196,196,196,196,196,196,196};
static int buttonLedH[10]={117,118,117,117,117,118,117,117,117,117};


static double Touch2LedRatio = (double)53.1/250; //size led = size touch * Touch2Led
static double ledPixRatio = 0.55;

static double ledWidth = 960;
static double ledHeight = 1152;


static int bSpacingX = 860 - 2*358;
static int bOffsetX = (1080-860)/2;
static int bOffsetY = 40;

#endif // POSITIONS_H
