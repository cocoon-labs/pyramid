/********************************************************************************
 * structure
 *
 * This tab contains all necessary functions for building the pyramid structure. 
 *
 * Copyright 2012 Neel Rao
 ********************************************************************************/

const byte coords[LEDS][3] PROGMEM = {  // Array containing the pixel coordinates in order of distance from the Arduino.
                                       {0,8,0},{0,7,0},{0,6,0},{0,5,0},{0,4,0},
                                       {0,3,0},{0,2,0},{0,1,0},{0,0,0},{0,1,1},
                                       {0,2,1},{0,2,2},{0,3,3},{0,3,2},{0,3,1},
                                       {0,4,1},{0,4,2},{0,4,3},{0,4,4},{0,5,5},
                                       {0,5,4},{0,5,3},{0,5,2},{0,5,1},{0,6,1},
                                       {0,6,2},{0,6,3},{0,6,4},{0,6,5},{0,6,6},
                                       {0,7,7},{0,7,6},{0,7,5},{0,7,4},{0,7,3},
                                       {0,7,2},{0,7,1},{0,8,1},{0,8,2},{0,8,3},
                                       {0,8,4},{0,8,5},{0,8,6},{0,8,7},{0,8,8},
                       
                                       {1,8,0},{1,8,1},{1,7,0},{1,6,0},{1,7,1},
                                       {1,8,2},{1,8,3},{1,7,2},{1,6,1},{1,5,0},
                                       {1,4,0},{1,3,0},{1,4,1},{1,5,1},{1,6,2},
                                       {1,7,3},{1,8,4},{1,8,5},{1,7,4},{1,6,3},
                                       {1,5,2},{1,4,2},{1,3,1},{1,2,0},{1,1,0},
                                       {1,0,0},{1,1,1},{1,2,1},{1,2,2},{1,3,2},
                                       {1,5,3},{1,4,3},{1,3,3},{1,4,4},{1,5,4},
                                       {1,6,4},{1,7,5},{1,6,5},{1,5,5},{1,6,6},
                                       {1,7,6},{1,8,6},{1,8,7},{1,7,7},{1,8,8},
                    
                                       {2,8,0},{2,7,0},{2,8,1},{2,8,2},{2,7,1},
                                       {2,6,0},{2,5,0},{2,6,1},{2,7,2},{2,8,3},
                                       {2,8,4},{2,7,3},{2,6,2},{2,5,1},{2,4,0},
                                       {2,3,0},{2,4,1},{2,5,2},{2,6,3},{2,7,4},
                                       {2,8,5},{2,8,6},{2,7,5},{2,6,4},{2,5,3},
                                       {2,4,2},{2,3,1},{2,2,0},{2,1,0},{2,0,0},
                                       {2,1,1},{2,2,1},{2,2,2},{2,3,2},{2,3,3},
                                       {2,4,3},{2,5,4},{2,4,4},{2,5,5},{2,6,5},
                                       {2,6,6},{2,7,6},{2,8,7},{2,7,7},{2,8,8}
                                     };

/* Builds the full pyramid structure.
 * Fills the row vectors of the pyramid with bytes
 * associating the pixels with their respective physical pyramid coordinates. */
void build_pyramid() {
  int i; // Variable for looping through the array of coordinate arrays.
  byte f,r,c;
  
  for (f=0; f<FACES; f++) {
    for (r=0; r<HEIGHT; r++) {
      byte b = 0;
      pyr[f][r].resize(r+1,b);
      /*Serial.print("Added row ");
      Serial.print(r,DEC);
      Serial.print(" on face ");
      Serial.print(f,DEC);
      Serial.println(".");
      delay(100);*/
    }
  }  
  for (i=0;i<LEDS;i++) {
    f = pgm_read_byte(&(coords[i][0])); // Pyramid face coordinate
    r = pgm_read_byte(&(coords[i][1])); // Pyramid row coordinate
    c = pgm_read_byte(&(coords[i][2])); // Pyramid column coordinate
    
    pyr[f][r][c]=i;
  }
}
