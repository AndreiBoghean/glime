#include "compat.h"
#include "stdint.h"
#include <cstdio>

void pollHeartRate()
{
  int bpm = get_hr_bpm();
  char bpm_s[4];
  // sprintf(bpm_s, "%03d", bpm);
  if (bpm) bpm = 0;
  bpm_s[0] = '1';
  bpm_s[1] = '2';
  bpm_s[2] = '3';
  bpm_s[3] = '\0';
  place_label(bpm_s, 100, 100);
}

int numba2 = 0;
void temp2() {
  clear_screen();
  numba2 = (numba2+1)%7;

  show_int(numba2);
  return;
}


int extern_main()
{
  set_colours(0x00FF00, 0xFFFF00);
  // TODO: CHANGE THE DEFAULT FG COLOUR SO IT'S NOT BLACK
  
  // start_read_hr();
  // register_timer_interrupt(pollHeartRate, 1000);
  register_timer_interrupt(temp2, 1000);
  return 0;
}
