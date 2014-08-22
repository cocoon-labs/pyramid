struct pixel *pulse(struct pixel *p) {
  static int freq = 10;
  static int time = 0;
  double factor = 0.5 + 0.5 * sin(time / freq);
  
  if (random(100)==0)
    freq = random(20) + 1;
  
  if (((1 - factor) < 0.01) && random(100)==0)
    pulse_on = !pulse_on;
  
  if (pulse_on) {
    p->R = factor * p->R;
    p->G = factor * p->G;
    p->B = factor * p->B;
  }
  
  time++;
  return p;
}
