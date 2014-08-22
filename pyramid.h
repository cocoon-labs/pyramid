#ifndef PYRAMID_H
#define PYRAMID_H
#define FACES 3 // Number of faces of the Pyramid
#define HEIGHT 9 // Number of rows of each face of the Pyramid
#define LEDS 135 // Number of LEDs (pixels) in the Pyramid

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define T_IN 4
#define T_OUT 5

#include <Arduino.h>
#include <vector>
#include <avr/pgmspace.h>
#include <math.h>

using namespace std;

/************* STRUCTS ******************************************************************/

/* A pixel structure holds its RGB values. */
struct pixel {
  byte R, G, B;
};

/************* FUNCTION PROTOTYPES *****************************************************************/

// structure
void build_pyramid();

// utility
void init_strand();
void update_strand();
void send_black_strand();
void setAtoB(struct pixel *, struct pixel *);
void addBtoA(struct pixel *, struct pixel *);
void subBfromA(struct pixel *, struct pixel *);
struct pixel *padd(byte, byte, byte);
struct pixel *random_pixel();

// pulse
struct pixel *pulse(struct pixel *);

// outline
void outline(int);
void shift_in(struct pixel *);
void shift_out(struct pixel *);

// rainbow
struct pixel *rainbow_increment_pixel(struct pixel *, int);
void rainbow_freak(int);
void rainbow_freak_pulse(int);
void rainbow_strobe(int);

// fht_rows
void fht_rows(int);
void fht_help();

// isis
struct pixel *isis_increment_pixel(struct pixel *, int);
void isis_pulse_all(int);
struct pixel *isis_pulse(struct pixel *);
byte isis_pulse_constrain(char, byte);
void isis_sound_freak(int);
struct pixel *isf_help(struct pixel *, byte, byte);
void isis_fht_rows(int);

//
void shift_down(struct pixel *);
void shift_up(struct pixel *);
void pulse_down(struct pixel *, int);
void set_all(struct pixel *p);
uint32_t Wheel(byte);
uint32_t generalWheel(byte, uint32_t, uint32_t, uint32_t);

#endif
