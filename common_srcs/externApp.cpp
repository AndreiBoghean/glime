#include "compat.h"
#include "stdint.h"

int numba2 = 0;
void pollHeartRate()
{
  // numba2 = (numba2+1)%7;
  // int bpm = 120+numba2; // get_hr_bpm();
  
  int bpm = get_hr_bpm();

  char bpm_s[4];
  bpm_s[0] = (char) 48+(bpm / 100);
  bpm_s[1] = (char) 48+((bpm % 100) / 10);
  bpm_s[2] = (char) 48+(bpm % 10);
  bpm_s[3] = '\0';

  clear_screen();
  place_label(bpm_s, 100, 70);
}


int extern_main()
{
  set_colours(0x00FF00, 0xFFFF00);
  // TODO: CHANGE THE DEFAULT FG COLOUR SO IT'S NOT BLACK
  
  start_read_hr();
  register_timer_interrupt(pollHeartRate, 1000);
  // register_timer_interrupt(temp2, 1000);
  return 0;
}
