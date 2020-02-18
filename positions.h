#ifndef POSITIONS_H
#define POSITIONS_H



static int buttonLedX[10]={250,206,161,206,250,621,665,710,665,621};
static int buttonLedY[10]={404,480,556,632,708,404,480,556,632,708};
static int buttonLedW[10]={89,89,89,89,89,89,89,89,89,89};
static int buttonLedH[10]={53,53,53,53,53,53,53,53,53,53};

static double Touch2LedRatio = (double)53.1/250; //size led = size touch * Touch2Led
static double ledPixRatio = 0.25;

static double ledWidth = 960;
static double ledHeight = 1152;


static int bSpacingX = 860 - 2*358;
static int bOffsetX = (1080-860)/2;
static int bOffsetY = 40;

#endif // POSITIONS_H
