/********************************************************************************
 * pyramid.ino
 *
 * This program controls a pyramid of LEDs connected in a single strand.
 * Pyramid can be of variable height and number of faces.
 * Assumptions:
 *   -LEDs are arranged on each face such that there is 1 on the top row,
 *    2 on the second row, then 3 on the third row, etc. No specific sequential
 *    order is necessary.
 *   -You must hardcode the exact placement of the strand of LEDs on the pyramid
 *    into the build_pyramid function. This is necessary, as there are numerous
 *    ways to string the wire around the pyramid, unless we were to require a 
 *    specific stringing method. This seems easier. The build_pyramid function
 *    is, however, the only place you need to do this. After that, the wonders
 *    of abstraction leave you worry free. 
 *
 * Copyright 2014 Neel Rao
 ********************************************************************************/
#define FHT_N 16 // set to 16 point fht
#define LOG_OUT 1 // use the log output function for fht

#define NUM_MODES 5 // number of program modes
#define M_FHT_ROWS 0
#define M_OUTLINE 1
#define M_FREAK 2
#define M_BOUNCE 3
#define M_SOUNDFREAK 4

#define NUM_SCHEMES 13 // number of color schemes
#define S_RAINBOW 0
#define S_CRISPY 1
#define S_SNOWSKIRT 2
#define S_ROYAL 3
#define S_GLEAM 4
#define S_FIRE 5
#define S_SPORKLE 6
#define S_DORK 7
#define S_KELPY 8
#define S_JUNGLE 9
#define S_AMERICA 10
#define S_GOBLIN 11
#define S_SEVENS 12

#include <Adafruit_NeoPixel.h>
#include <SPI.h>
#include <TCL.h>
#include <FHT.h>
#include <StandardCplusplus.h>
#include <system_configuration.h>
#include <unwind-cxx.h>
#include <utility.h>
#include "pyramid.h"

Adafruit_NeoPixel strip = Adafruit_NeoPixel(1, 3, NEO_GRB + NEO_KHZ400);

uint16_t updateInterval = 200; // Milliseconds between color updates

uint8_t mode = M_OUTLINE;   // Program mode selected
uint8_t scheme = S_ROYAL; // Color scheme selected

uint8_t shiftBy = 30;
uint8_t wheelPos = 0;
boolean pulse_on = true;

uint8_t pulsePos = HEIGHT - 1;
uint8_t pulseDir = UP;

uint8_t fadeFactor = 3;
uint8_t chance = 100;

uint8_t vertDir = UP;
uint8_t horiDir = LEFT;
uint8_t triDir = T_IN;
uint8_t genDir = UP;

struct pixel p = {0,0,255};

struct pixel pixels[LEDS]; // Current pixel values are stored in this array.
vector<byte> pyr[FACES][HEIGHT]; // Our pyramid.

/**********************************************************************
 * BODY
 **********************************************************************/

/* Initialize the SPI bus & set pixels to black. */
void setup() {
  int i;
  
  TCL.begin();  // Begin protocol for communicating with the TCL strand
  TCL.setupDeveloperShield(); // Set up developer shield for inputs
  //Serial.begin(57600); // Start serial communication

  build_pyramid(); // Initialize our pyramid structure
  init_strand(); // Send black pixels to the strand to turn off all LEDs.
  //Serial.println("Before loop.");
  randomSeed(analogRead(0));
  randomize();
  delay(100);
}

/* This is the main looping function. */
void loop() {
  randomize();
  
  switch (mode) {
    case M_FHT_ROWS:
      fht_rows();
      break;
    case M_OUTLINE:
      outline();
      break;
    case M_FREAK:
      freak();
      break;
    case M_BOUNCE:
      bounce();
      break;
    case M_SOUNDFREAK:
      soundFreak();
      break;
  }
}
