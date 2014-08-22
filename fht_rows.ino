#define FHT_N 16 // set to 16 point fht
#define LOG_OUT 1 // use the log output function for fht

#include <FHT.h>

void fht_rows() {
  int factor = 2048;
  
  fht_help();
  
  setRtoC(8, scaleColor(Wheel(wheelPos & 255), fht_log_out[0], factor));
  wheelPos += shiftBy;
  setRtoC(7, scaleColor(Wheel(wheelPos & 255), fht_log_out[1], factor));
  wheelPos += shiftBy;
  setRtoC(6, scaleColor(Wheel(wheelPos & 255), fht_log_out[2], factor));
  wheelPos += shiftBy;
  setRtoC(5, scaleColor(Wheel(wheelPos & 255), fht_log_out[3], factor));
  wheelPos += shiftBy;
  setRtoC(4, scaleColor(Wheel(wheelPos & 255), fht_log_out[4], factor));
  wheelPos += shiftBy;
  setRtoC(3, scaleColor(Wheel(wheelPos & 255), fht_log_out[5], factor));
  wheelPos += shiftBy;
  setRtoC(2, scaleColor(Wheel(wheelPos & 255), fht_log_out[6], factor));
  wheelPos += shiftBy;
  setRtoC(1, scaleColor(Wheel(wheelPos & 255), fht_log_out[7], factor));
  wheelPos += shiftBy;
    
  int sensorValue = analogRead(A0);
  p.R = sensorValue>>2;
  p.G = sensorValue>>2;
  p.B = sensorValue>>2;
  setRtoC(0, getCofP(&p));
    
  update_strand(); // Send the updated pixels to the strand.    
  delay(updateInterval); // Delay next update by updateInterval milliseconds.
}

void fht_help() {
  cli();
  for (int i = 0 ; i < FHT_N ; i++) { // save 256 samples
    int sensorValue = analogRead(A0)+analogRead(A2); // form into an int
    fht_input[i] = sensorValue; // put real data into bins
  }
  fht_window(); // window the data for better frequency response
  fht_reorder(); // reorder the data before doing the fht
  fht_run(); // process the data in the fht
  fht_mag_log(); // take the output of the fht
  sei();
        
  if (fht_log_out[0] < 140)
    fht_log_out[0] = 0;
  if (fht_log_out[1] < 128)
    fht_log_out[1] = 0;
  if (fht_log_out[2] < 112)
    fht_log_out[2] = 0;
  if (fht_log_out[3] < 96)
    fht_log_out[3] = 0;
  if (fht_log_out[4] < 96)
    fht_log_out[4] = 0;
  if (fht_log_out[5] < 96)
    fht_log_out[5] = 0;
  if (fht_log_out[6] < 104)
    fht_log_out[6] = 0;
  if (fht_log_out[7] < 104)
    fht_log_out[7] = 0;
}
