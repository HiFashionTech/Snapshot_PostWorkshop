// NeoWindow.h
// NeoWindow defines a Window (region) of a NeoPixel strip and some effects to be performed in it
// goal is to avoid using the delay() function and
// allow multiple strips/windows/effects to be displayed concurrently

#ifndef _NEOWINDOW_
#define _NEOWINDOW_

// all based on the NeoPixel library from Adafruit
#include <AdaFruit_NeoPixel.h>

// and our NeoStrip object that encapsulates the Pixel
#include "NeoStrip.h"

class NeoWindow 
{
private:
  // for use herein.
  typedef void (NeoWindow::*NeoWindowUpdateFunc)(void);
  
// class variables
    static uint32_t currTime; // current Millis 
    static int s_nIDGenerator;

public:
  // Instance Constructor:
  NeoWindow(NeoStrip *strip, int startPixel, int len);

  // Class functions
  static void updateTime() {NeoWindow::currTime = millis();}
  static uint32_t currentTime() {return NeoWindow::currTime;}

  /////////////////////////
  // instance functions

  void updateWindow(void); // invoke the current effect function
  boolean effectDone(void) {return efxDone;}
  
  void printId(void);
  void printData(void);
  void fillColor(uint32_t color);
  void fillBlack();

// hidden Instance Functions
private:
  // pointer to the current effect's update function
  // encapsulating the effect variables, etc
  NeoWindowUpdateFunc curUpdateFunc;
  
/// Instance vars & methods
  NeoStrip *myStrip; // the strip I belong to
  uint16_t myId; // for idenfying the window
  uint16_t myStartPixel; // absolute index of start pixel in this window
  uint16_t myPixelCount;  // number of pixels in this window
  uint16_t myEndPixel;    // absolute index of last pixel in this window

  boolean efxDone;  // set when current effect is complete, if ever

  uint32_t lastTime; // the last time current effect updated
  uint32_t effectDelay; // delay between updates of current effect

  
 ////////////
 // Different effects go here
// instance variables to support specific effects
// cleaner design might move these into some sort of Helper Class
// for each effect there is a public/private section
// public section defines the setXXXEfx function, and maybe exposes some stuff
// private section hides the effect function's instance variables
//// there should be some OO techinque for better implmenting this but sometime for later
   
// addtional code for other efx later or in subclass
//  void setPongEfx(uint32_t color, uint32_t delayTime);
//  void setRainbowEfx(uint32_t delayTime);

public:
  void setCircleEfx(uint32_t color, uint32_t delayTime); // Circle one pixel of color around window
private:
  // circle Effect
  void circleUpdateEfx(void); 
  uint32_t circle_color;
  int circle_cursor; // absolute index of currently active pixel

public:
  void setWipeEfx(uint32_t color, uint32_t delayTime); // Wipe color once around window
private:
  // wipe once and then set Done
  void wipeUpdateEfx(void);
  uint32_t wipe_color;
  int32_t wipe_cursor;

public:
  void setBlinkEfx(uint32_t color, uint32_t delayTime, int count = 0);
private:
  void blinkUpdateEfx(void);
  uint32_t blink_color;
  boolean blink_state;
  int blink_maxCount;
  int blink_step;
  
};


#endif
