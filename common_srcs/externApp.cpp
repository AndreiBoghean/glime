#include "compat.h"
#include "stdint.h"

int numba2 = 0;
void pollHeartRate()
{
  int bpm = 120+numba2; // get_hr_bpm();
  
  // int bpm = get_hr_bpm();

  char bpm_s[4];
  bpm_s[0] = (char) 48+(bpm / 100);
  bpm_s[1] = (char) 48+((bpm % 100) / 10);
  bpm_s[2] = (char) 48+(bpm % 10);
  bpm_s[3] = '\0';

  clear_screen();
  place_label(bpm_s, 60, 180);
}

void incrementer()
{
  numba2 = (numba2+1)%8;
}

int OnTouchEvent(enum globalTouchEvent event)
{
	clear_screen(); // prepare for drawing the next screen state.
	place_label("yoted", 10, 200);
	place_label("dotey", 60, 200);
	return 1;
}

int extern_main()
{
  set_colours(0x00FF00, 0xAAAA00);
  clear_screen();
  place_label("work", 10, 10);
  place_label("please", 100, 10);
  register_global_eventListener(OnTouchEvent);
  // TODO: CHANGE THE DEFAULT FG COLOUR SO IT'S NOT BLACK
  
  // start_read_hr();
  register_timer_interrupt(incrementer, 1000);
  register_timer_interrupt(pollHeartRate, 500);
  return 0;
}
