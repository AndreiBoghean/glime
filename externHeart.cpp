#include "compat.h"
#include "stdint.h"

void pollHeartRate()
{
  int bpm = get_hr_bpm();
  if (bpm == 0) return;

  char bpm_s[9] = "bpm ___ ";
  bpm_s[4] = (char) 48+(bpm / 100);
  bpm_s[5] = (char) 48+((bpm % 100) / 10);
  bpm_s[6] = (char) 48+(bpm % 10);

  clear_screen();
  place_label(bpm_s, 60, 120);
}

int extern_main()
{
  set_colours(0xFF0000, 0x000000);
  clear_screen();
  // TODO: CHANGE THE DEFAULT FG COLOUR SO IT'S NOT BLACK
  
  place_label("bpm ___?", 60, 120);
  start_read_hr();
  register_timer_interrupt(pollHeartRate, 125);
  return 0;
}
