/********************************************************************************
 * utility
 *
 * This tab contains basic utility functions for maintaining the pyramid. 
 *
 * Copyright 2012 Neel Rao
 ********************************************************************************/
 
 /* Initializes all pixels with black. LEDs are strung in increments of 25,
 * so it is important to set any unused pixels to black, in the event of relic colors. */
void init_strand() {
  int i;  // Variable to iterate through all LEDs

  TCL.sendEmptyFrame();
  for(i=0;i<LEDS;i++) {
    pixels[i].R = pixels[i].G = pixels[i].B = 0;
    TCL.sendColor(0,0,0);
  }
  for(i=LEDS;i<LEDS+(25-LEDS%25);i++) {
    TCL.sendColor(0,0,0);
  }
  TCL.sendEmptyFrame();
}

/* Updates the pixel strand with the values currently stored in the pixels array.
 * The pixel nearest the Arduino is the first element of the array.               */
void update_strand() {
  int i; // Variable to iterate through LEDs in use
// TO DIM DIVIDE BY 8
  TCL.sendEmptyFrame();
  for(i=0;i<LEDS;i++) {
    TCL.sendColor(pixels[i].R,pixels[i].G,pixels[i].B);
  }
  TCL.sendEmptyFrame();
  
  TCL.sendEmptyFrame();
  for(i=0;i<LEDS;i++) {
    TCL.sendColor(pixels[i].R,pixels[i].G,pixels[i].B);
  }
  TCL.sendEmptyFrame();
}

/* Updates the pixel strand with the values currently stored in the pixels array.
 * The pixel nearest the Arduino is the first element of the array.               */
void send_black_strand() {
  int i; // Variable to iterate through LEDs in use

  TCL.sendEmptyFrame();
  for(i=0;i<LEDS;i++) {
    TCL.sendColor(0,0,0);
  }
  TCL.sendEmptyFrame();
  
  TCL.sendEmptyFrame();
  for(i=0;i<LEDS;i++) {
    TCL.sendColor(0,0,0);
  }
  TCL.sendEmptyFrame();
}

/* Given a pointer to pixel A and a pointer to pixel B,
 * this function sets the color of A to the color of B. */
void setAtoB(struct pixel *pA, struct pixel *pB) {
  pA->R = pB->R;
  pA->G = pB->G;
  pA->B = pB->B;
}

/* Given a pointer to a pixel p and a color Color,
 * this function sets the color of p to Color. */
void setPtoC(struct pixel *p, uint32_t Color) {
  p->R = Color >> 16;
  p->G = (Color >> 8) & 255;
  p->B = Color & 255;
}

/* Given a row r and a color Color,
 * this function sets the color of r to Color. */
void setRtoC(uint8_t r, uint32_t Color) {
  uint8_t f,c;
  
  for (f=0; f<FACES; f++) {
    for (c=0 ; c<r+1 ; c++) {
      setPtoC(padd(f,r,c), Color);
    }
  }
}

/* Given a pointer to a pixel p,
 * this function returns the color of p. */
uint32_t getCofP(struct pixel *p) {
  uint32_t r = p->R;
  uint32_t g = p->G;
  uint32_t b = p->B;
  return (r << 16) | (g << 8) | b;
}

/* Given a pointer to pixel A and a pointer to pixel B,
 * this function adds the color of B to the color of A. */
void addBtoA(struct pixel *pA, struct pixel *pB) {
  if ((pA->R + pB->R) > 255)
    pA->R = 255;
  else 
    pA->R += pB->R;
  if ((pA->G + pB->G) > 255)
    pA->G = 255;
  else 
    pA->G += pB->G;
  if ((pA->B + pB->B) > 255)
    pA->B = 255;
  else 
    pA->B += pB->B;
}

/* Given a pointer to pixel A and a pointer to pixel B,
 * this function subtracts the color of B from the color of A. */
void subBfromA(struct pixel *pA, struct pixel *pB) {
  if ((pA->R - pB->R) < 0)
    pA->R = 0;
  else 
    pA->R -= pB->R;
  if ((pA->G - pB->G) < 0)
    pA->G = 0;
  else 
    pA->G -= pB->G;
  if ((pA->B - pB->B) < 0)
    pA->B = 0;
  else 
    pA->B -= pB->B;
}

/* Given coordinates, returns a pointer to the respective pixel. */
struct pixel *padd(byte face, byte row, byte col) {
  return &pixels[pyr[face][row][col]];
}

/* Returns a pointer to a random pixel. */
struct pixel *random_pixel() {
  int f = random(FACES);
  int r = random(HEIGHT);
  int c = random(r+1);
  return padd(f,r,c);
}

void shift(struct pixel *p, uint8_t dir) {
  int f, r, c;
  
  for (f=0; f<FACES; f++) {
    switch (dir) {
      case UP:
        // Shift colors up row by row, starting from the top
        for (r=0; r<HEIGHT-1; r++){
          for (c=0; c<r+1; c++){ // Set the current pixel's color to that of the below pixel in its column
            setAtoB(padd(f,r,c), padd(f,r+1,c));
          }
        }
        // Set the bottom row to be the same color as the input pixel
        for (c=0; c<HEIGHT; c++){
          setAtoB(padd(f,HEIGHT-1,c), p);
        }
        break;
      case DOWN:
        // Shift colors down row by row, starting from the bottom
        for (r=HEIGHT-1; r>0; r--){
          for (c=0; c<r; c++){ // Set the current pixel's color to that of the above pixel in its column
            setAtoB(padd(f,r,c), padd(f,r-1,c));
          }
          // Set the color of the last pixel of the row to be the same as its row
          setAtoB(padd(f,r,r), padd(f,r,0));
        }
        // Set the top pixel to be the same color as the input pixel
        setAtoB(padd(f,0,0), p);
        break;
      case LEFT:
        // Shift colors left col by col, starting from the left
        for (c=0; c<HEIGHT-1; c++){
          for (r=HEIGHT-1; r>c; r--){ // Set the current pixel's color to that of the right pixel in its row
            setAtoB(padd(f,r,c), padd(f,r,c+1));
          }
          // Set the color of the top pixel of the col to be the same as its col
          setAtoB(padd(f,c,c), padd(f,HEIGHT-1,c));
        }
        // Set the right pixel to be the same color as the input pixel
        setAtoB(padd(f,HEIGHT-1,HEIGHT-1), p);
        break;
      case RIGHT:
        // Shift colors right col by col, starting from the right
        for (c=HEIGHT-1; c>0; c--){
          for (r=HEIGHT-1; r>c-1; r--){ // Set the current pixel's color to that of the left pixel in its row
            setAtoB(padd(f,r,c), padd(f,r,c-1));
          }
        }
        // Set the left col to be the same color as the input pixel
        for (r=0; r<HEIGHT; r++){
          setAtoB(padd(f,r,0), p);
        }
        break;
      case T_IN:
        shift_in(p);
        break;
      case T_OUT:
        shift_out(p);
        break;
    }
  }
}

uint32_t fadeFactory(uint32_t color) {
  return scaleColor(color, 2, fadeFactor);
}

void fadeAll() {
  uint8_t f, r, c;
  uint32_t color;
  
  for (f=0; f<FACES; f++) {
    for (r=0 ; r<HEIGHT ; r++) {
      for (c=0 ; c<r+1 ; c++) {
        color = getCofP(padd(f,r,c));
        color = fadeFactory(color);
        setPtoC(padd(f,r,c), color);
      }
    }
  }
}

uint32_t scaleColor(uint32_t color, int mul, int div) {
  uint32_t r = (color >> 16) * mul / div;
  uint32_t g = ((color >> 8) & 255) * mul / div;
  uint32_t b = (color & 255) * mul / div;
  if (r > 255) r = 255;
  if (g > 255) g = 255;
  if (b > 255) b = 255;
  return (r << 16) | (g << 8) | b;
}

void randomize () {
  if (!random(chance)) {
    if (vertDir == UP) vertDir = DOWN;
    else vertDir = UP;
  }
  if (!random(chance)) {
    if (horiDir == LEFT) horiDir = RIGHT;
    else horiDir = LEFT;
  }
  if (!random(chance)) {
    if (triDir == T_IN) triDir = T_OUT;
    else triDir = T_IN;
  }
  if (!random(chance)) {
    genDir = random(4);
  }
  if (!random(chance)) {
    shiftBy = random(50);
  }
  if (!random(chance)) {
    updateInterval = 50 + random(200);
  }
  if (!random(chance)) {
    fadeFactor = 2 + random(10);
  }
  if (!random(chance)) {
    scheme = random(NUM_SCHEMES);
  }
  if (!random(chance)) {
    mode = random(NUM_MODES);
  }
}

/**********************************************************************
 * HELPER FUNCTIONS
 **********************************************************************/

/* Given a pointer to a pixel,
 * this function shifts the colors of the pyramid down one row,
 * and sets the color of the top row to the color of the input pixel. */
void shift_down(struct pixel *p) {
  int f, r, c; // Variables for looping
  
  for (f=0;f<FACES;f++){
    // Shift colors down row by row, starting from the bottom
    for (r=HEIGHT-1;r>0;r--){
      for (c=0;c<r;c++){ // Set the current pixel's color to that of the above pixel in its column
        setAtoB(padd(f,r,c),padd(f,r-1,c));
      }
      // Set the color of the last pixel of the row to be the same as its row
      setAtoB(padd(f,r,r),padd(f,r,0));
    }
    // Set the top pixel to be the same color as the input pixel
    setAtoB(padd(f,0,0),p);
  }
}

/* Given a pointer to a pixel,
 * this function shifts the colors of the pyramid up one row,
 * and sets the color of the bottom row to the color of the input pixel. */
void shift_up(struct pixel *p) {
  int f, r, c; // Variables for looping
  
  for (f=0;f<FACES;f++){
    // Shift colors up row by row, starting from the top
    for (r=0;r<HEIGHT-1;r++){
      for (c=0;c<r+1;c++){ // Set the current pixel's color to that of the below pixel in its column
        setAtoB(padd(f,r,c),padd(f,r+1,c));
      }
    }
    // Set the bottom row to be the same color as the input pixel
    for (c=0;c<HEIGHT;c++){
      setAtoB(padd(f,HEIGHT-1,c),p);
    }
  }
}

/* Given a pointer to a pixel and an integer,
 * this function sends pulses down the pyramid of the color of the input pixel,
 * spaced apart by the number of rows specified.                                */
void pulse_down(struct pixel *p, int freq) {
  static int i = 0; // Variable for looping
  static struct pixel black = {0,0,0};
  if (i % freq == 0)
    shift_down(p);
  else
    shift_down(&black);
  i++;
}

/* Given a pointer to a pixel,
 * this function sets the colors of the entire pyramid to the color of the input pixel. */
void set_all(struct pixel *p) {
  int f, r, c; // Variables for looping
  
  for (f=0;f<FACES;f++){
    for (r=0;r<HEIGHT;r++){
      for (c=0;c<r+1;c++){ // Set the current pixel's color to that of the input pixel
        setAtoB(padd(f,r,c),p);
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
uint32_t Wheel(byte WheelPos) {
  // Use selected color scheme.
  switch (scheme) {
    case S_RAINBOW: // 
      return generalWheel(WheelPos, strip.Color(255,0,0), strip.Color(0,255,0), strip.Color(0,0,255));
    case S_CRISPY: //
      return generalWheel(WheelPos, strip.Color(2,255,222), strip.Color(229,149,217), strip.Color(210,255,0));
    case S_SNOWSKIRT: //
      return generalWheel(WheelPos, strip.Color(229,255,46), strip.Color(240,23,0), strip.Color(147,0,131));
    case S_ROYAL: //
      return generalWheel(WheelPos, strip.Color(0,0,0), strip.Color(128,0,255), strip.Color(128,0,128));
    case S_GLEAM: //
      return generalWheel(WheelPos, strip.Color(0,0,0), strip.Color(23,7,0), strip.Color(85,60,0));
    case S_FIRE: //
      return generalWheel(WheelPos, strip.Color(255,0,0), strip.Color(255,100,0), strip.Color(232,120,0));
    case S_SPORKLE: //
      return generalWheel(WheelPos, strip.Color(0,0,0), strip.Color(80,0,230), strip.Color(0,0,0));
    case S_DORK: //
      return generalWheel(WheelPos, strip.Color(0,0,0), strip.Color(196,0,255), strip.Color(209,209,209));
    case S_KELPY: //
      return generalWheel(WheelPos, strip.Color(0,0,133), strip.Color(0,196,255), strip.Color(0,240,44));
    case S_JUNGLE: //
        return generalWheel(WheelPos, strip.Color(214,185,0), strip.Color(0,255,17), strip.Color(60,138,80));
    case S_AMERICA: //
      return generalWheel(WheelPos, strip.Color(255,0,0), strip.Color(209,209,209), strip.Color(0,0,255));
    case S_GOBLIN: //
      return generalWheel(WheelPos, strip.Color(0,255,0), strip.Color(52,146,52), strip.Color(17,181,119));
    case S_SEVENS: //
      return generalWheel(WheelPos, strip.Color(117,0,177), strip.Color(77,17,71), strip.Color(247,77,7));
  }
}

// Given a value 0 to 255 and three colors,
// returns the respective color on the color wheel
// created by the specified colors.
uint32_t generalWheel(byte WheelPos, uint32_t C0, uint32_t C1, uint32_t C2) {
  uint8_t r0 = C0 >> 16;
  uint8_t g0 = (C0 >> 8) & 255;
  uint8_t b0 = C0 & 255;
  uint8_t r1 = C1 >> 16;
  uint8_t g1 = (C1 >> 8) & 255;
  uint8_t b1 = C1 & 255;
  uint8_t r2 = C2 >> 16;
  uint8_t g2 = (C2 >> 8) & 255;
  uint8_t b2 = C2 & 255;
  
  if(WheelPos < 85) {
   return strip.Color(r0 + (WheelPos * (r1 - r0) / 85), g0 + (WheelPos * (g1 - g0) / 85), b0 + (WheelPos * (b1 - b0) / 85));
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(r1 + (WheelPos * (r2 - r1) / 85), g1 + (WheelPos * (g2 - g1) / 85), b1 + (WheelPos * (b2 - b1) / 85));
  } else {
   WheelPos -= 170;
   return strip.Color(r2 + (WheelPos * (r0 - r2) / 85), g2 + (WheelPos * (g0 - g2) / 85), b2 + (WheelPos * (b0 - b2) / 85));
  }
}

void incrementPulsePos() {
  if (pulseDir == DOWN) {
    if (pulsePos < HEIGHT - 1) {
      pulsePos++;
    } else {
      pulsePos--;
      pulseDir = UP;
    }
  } else if (pulseDir == UP) {
    if (pulsePos > 0) {
      pulsePos--;
    } else {
      pulsePos++;
      pulseDir = DOWN;
    }
  }
}


/* Given a pointer to a pixel,
 * this function shifts the outline of the pyramid in one level,
 * and sets the color of the outer triangle to the color of the input pixel. */
void shift_in(struct pixel *p) {
  int f,r,c; // Variables for looping
  
  for (f=0;f<FACES;f++){
    // Set inner triangle
    for (int i=0; i<6; i++) {
      r = pgm_read_byte(&(triangle_inner[i][0]));
      c = pgm_read_byte(&(triangle_inner[i][1]));
      setAtoB(padd(f,r,c),padd(f,2,1));
    }
    // Set middle triangle
    for (int i=0; i<15; i++) {
      r = pgm_read_byte(&(triangle_mid[i][0]));
      c = pgm_read_byte(&(triangle_mid[i][1]));
      setAtoB(padd(f,r,c),padd(f,0,0));
    }
    // Set outer triangle
    for (int i=0; i<24; i++) {
      r = pgm_read_byte(&(triangle_outer[i][0]));
      c = pgm_read_byte(&(triangle_outer[i][1]));
      setAtoB(padd(f,r,c),p);
    }
  }
}

/* Given a pointer to a pixel,
 * this function shifts the outline of the pyramid out one level,
 * and sets the color of the inner triangle to the color of the input pixel. */
void shift_out(struct pixel *p) {
  int f,r,c; // Variables for looping
  
  for (f=0;f<FACES;f++){
    // Set outer triangle
    for (int i=0; i<24; i++) {
      r = pgm_read_byte(&(triangle_outer[i][0]));
      c = pgm_read_byte(&(triangle_outer[i][1]));
      setAtoB(padd(f,r,c),padd(f,2,1));
    }
    // Set middle triangle
    for (int i=0; i<15; i++) {
      r = pgm_read_byte(&(triangle_mid[i][0]));
      c = pgm_read_byte(&(triangle_mid[i][1]));
      setAtoB(padd(f,r,c),padd(f,4,2));
    }
    // Set inner triangle
    for (int i=0; i<6; i++) {
      r = pgm_read_byte(&(triangle_inner[i][0]));
      c = pgm_read_byte(&(triangle_inner[i][1]));
      setAtoB(padd(f,r,c),p);
    }
  }
}

