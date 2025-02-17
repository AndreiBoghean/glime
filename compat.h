#pragma once

#include <stdint.h>

/*
  notes:
  valid positions for x/y arguments are 0 <= x/y <= 240.
  0,0 is top left.

  the background and foreground colours are by default white on black,
  and are used for the default where possible e.g. place_label, show_int, draw_rect.
*/

// init function with room for arbitrary args. this is for internal use by the implementer of glime within a watch OS, and should not concern most people.
void init(void* setups);

// places a label centrered at x, y.
void place_label(const char* string, int x, int y);
// places an integer in the centre of the screen. mostly for debugging. only supports integers 0-9.
void show_int(int i);

enum buttonTouchEvent {btn_shortClick, btn_released, btn_pressLost, btn_longPress, btn_longPressRepeat};
typedef void (*buttonCallback) (enum buttonTouchEvent);
void place_button(buttonCallback, int x, int y);

void* counter_create(int startVal, int min, int max, int x, int y);
int counter_get(void* counter);
void counter_set(void* counter, int newVal);
void counter_render(void* counter);

// set the foreground and background colours for drawing.
// arguments are in the form of hexadecimal, e.g. set_colours(0x0000FF, 0xFFFF00) to set to blue foreground on yellow background. 
void set_colours(uint32_t fg, uint32_t bg);

enum brightness_level {lo, med, hi};
void set_brightness(enum brightness_level bl);

enum globalTouchEvent {Tap, TapDouble, TapLong, SwipeLeft, SwipeRight, SwipeUp, SwipeDown};
typedef int (*touchCallback)(enum globalTouchEvent e);
void register_global_eventListener(touchCallback e);
// ^ callback returns a boolean according to whether it actioned on the event or not
// if it DID action, then we finalise that "event" and move on to detecting the next one.
// internal note: we use the return to decide whether to call lvgl.CancelTap();

// similar as above, but detects solely tap events, and makes available the x/y positions of the event. 
typedef int (*touchCallback_xy)(uint16_t x, uint16_t y);
void register_global_eventListener_xy(touchCallback_xy e);

void disable_sleep();

void clear_screen();

void draw_rect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

void start_read_hr();
void stop_read_hr();
int get_hr_bpm();

// a timer_interrupt should be used when the application is actively running; for passive background timers see below.
typedef void (*timer_interrupt_callback)();
void register_timer_interrupt(timer_interrupt_callback action, int period_ms);

// these can be used for proper background timers that still countdown even when the application is backgrounded or the watch goes to sleep.
void* timer_create(timer_interrupt_callback action, int period_ms);
void timer_setPeriod(void* timer, int newPeriod);
void timer_start(void*);
void timer_stop(void*);
int timer_isRunning(void* timer);
int timer_msRemaining(void* timer);
