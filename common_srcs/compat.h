#pragma once

#include <stdint.h>

void init(void* setups);
void show_int(int i);

// places a label centrered at x, y.
void place_label(const char* string, int x, int y);

void set_colours(uint32_t fg, uint32_t bg);
// set the foreground and background colours for drawing.

enum brightness_level {lo, med, hi};
void set_brightness(enum brightness_level bl);

enum globalTouchEvent {Tap, SwipeLeft, SwipeRight};
typedef int (*touchCallback)(enum globalTouchEvent e);
void register_global_eventListener(touchCallback e);
// ^ callback returns a boolean according to whether it actioned on the event or not
// if it DID action, then we finalise that "event" and move on to detecting the next one.
// i.e. we use the return to decide whether to call lvgl.CancelTap();

void disable_sleep();

void clear_screen();
