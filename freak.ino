void freak() {
  setPtoC(&p, Wheel(wheelPos & 255));
  shift(&p, genDir);
    
  wheelPos += shiftBy;
    
  update_strand(); // Send the updated pixels to the strand.    
  delay(updateInterval); // Delay next update by updateInterval milliseconds.
}

void soundFreak() {
  int factor = 4096;
  uint32_t color;
  
  fht_help();
  
  switch (genDir) {
    case UP:
        color = scaleColor(Wheel(wheelPos & 255), fht_log_out[0] + fht_log_out[1], factor);
        break;
      case DOWN:
        color = scaleColor(Wheel(wheelPos & 255), fht_log_out[6] + fht_log_out[7], factor);
        break;
      case LEFT:
        color = scaleColor(Wheel(wheelPos & 255), fht_log_out[2] + fht_log_out[3], factor);
        break;
      case RIGHT:
        color = scaleColor(Wheel(wheelPos & 255), fht_log_out[4] + fht_log_out[5], factor);
        break;
  }
  
  setPtoC(&p, color);
  shift(&p, genDir);
    
  wheelPos += shiftBy;
    
  update_strand(); // Send the updated pixels to the strand.    
  delay(updateInterval); // Delay next update by updateInterval milliseconds.
}
