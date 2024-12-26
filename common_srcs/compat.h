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

enum globalTouchEvent {Tap, TapDouble, TapLong, SwipeLeft, SwipeRight, SwipeUp, SwipeDown};
typedef int (*touchCallback)(enum globalTouchEvent e);
void register_global_eventListener(touchCallback e);
// ^ callback returns a boolean according to whether it actioned on the event or not
// if it DID action, then we finalise that "event" and move on to detecting the next one.
// i.e. we use the return to decide whether to call lvgl.CancelTap();

typedef int (*touchCallback_xy)(uint16_t x, uint16_t y);
void register_global_eventListener_xy(touchCallback_xy e);

void disable_sleep();

void clear_screen();

void draw_rect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
