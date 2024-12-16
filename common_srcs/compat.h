#pragma once

#include <cstdint>
#include <string>

void init(void* setups);
void show_int(int i);

#if true
void place_label(std::string text, int x, int y);
// places a label centrered at x, y.

void set_colours(uint32_t, uint32_t);
// set the foreground and background colours for drawing.

enum brightness_level {lo, med, hi};
void set_brightness(brightness_level);

enum globalTouchEvent {Tap, SwipeLeft, SwipeRight};
typedef bool (*touchCallback)(globalTouchEvent e);
void register_global_eventListener(touchCallback e);
// ^ callback returns a boolean according to whether it actioned on the event or not
// if it DID action, then we finalise that "event" and move on to detecting the next one.
// i.e. we use the return to decide whether to call lvgl.CancelTap();

void disable_sleep();
#endif
