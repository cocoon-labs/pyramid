void bounce() {
  fadeAll();
  
  setRtoC(pulsePos, Wheel(wheelPos & 255));
  
  incrementPulsePos();
  
  wheelPos += shiftBy;
  
  update_strand(); // Send the updated pixels to the strand.    
  delay(updateInterval); // Delay next update by updateInterval milliseconds.
}
