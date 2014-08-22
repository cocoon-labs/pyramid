const byte triangle_outer[24][2] PROGMEM = { 
                                             {0,0},
                                             {1,0},{1,1},
                                             {2,0},{2,2},
                                             {3,0},{3,3},
                                             {4,0},{4,4},
                                             {5,0},{5,5},
                                             {6,0},{6,6},
                                             {7,0},{7,7},
                                             {8,0},{8,1},{8,2},{8,3},{8,4},{8,5},{8,6},{8,7},{8,8}
                                           };
                                          
const byte triangle_mid[15][2] PROGMEM = { 
                                           {2,1},
                                           {3,1},{3,2},
                                           {4,1},{4,3},
                                           {5,1},{5,4},
                                           {6,1},{6,5},
                                           {7,1},{7,2},{7,3},{7,4},{7,5},{7,6}
                                         };
                                         
const byte triangle_inner[6][2] PROGMEM = {
                                            {4,2},
                                            {5,2},{5,3},
                                            {6,2},{6,3},{6,4}
                                          };

void outline() {
  setPtoC(&p, Wheel(wheelPos & 255));
  /*shift(&p, triDir);
  
  wheelPos += shiftBy;*/
  switch (triDir) {
      case T_IN:
        wheelPos += shiftBy;
        shift_in(&p);
        break;
      case T_OUT:
        wheelPos -= shiftBy;
        shift_out(&p);
        break;
  };
    
  update_strand(); // Send the updated pixels to the strand.    
  delay(updateInterval); // Delay next update by updateInterval milliseconds.
}
