#include "compat.h"
#include "stdint.h"

int OnTouchEvent(enum globalTouchEvent event); // forward declare
int OnTouchEvent_xy(uint16_t x, uint16_t y); // forward declare

int extern_main()
{
  register_global_eventListener(OnTouchEvent);
  register_global_eventListener_xy(OnTouchEvent_xy);
  return 0;
}

int colI = 10000; // start with a large number so the user cant immediately swipe to go negative
int size = 10;
int OnTouchEvent_xy(uint16_t x, uint16_t y)
{
  // clear_screen(); // prepare for drawing the next screen state.

  uint32_t colours[] = {0xFF0000, 0xFF00FF, 0xFFFF00, 0x00FFFF, 0x0000FF};

  set_colours(colours[colI % 5], 0x0);
  draw_rect(x, y, x+size, y+size);
  // SetColors();
  return 1;
}

int OnTouchEvent(enum globalTouchEvent event)
{
	if (event == SwipeLeft)
	{
		colI--;
		return 1;
	}
	else if (event == SwipeRight) {
		colI++;
		return 1;
	}
	return 1; // we actually want to return 1, so that swipe up / down events arent aditionally processed and subsequently trigger the app close gesture
}
