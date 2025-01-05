#include "compat.h"
// #include "src/displayapp/screens/Screen.h"
#include "displayapp/screens/Screen.h"

// #include "src/components/brightness/BrightnessController.h"
#include "components/brightness/BrightnessController.h"
// #include "src/displayapp/Controllers.h"
#include "displayapp/Controllers.h"

#include "displayapp/screens/Screen.h"
#include "components/brightness/BrightnessController.h"
#include "systemtask/SystemTask.h"
#include <cstdint>
#include <cstdlib>
#include <lvgl/lvgl.h>

#include "displayapp/LittleVgl.h"
#include "components/motor/MotorController.h"

#include "components/heartrate/HeartRateController.h"

// note: callback returns a boolean according to whether it actioned on the event or not
// if it DID action, then we finalise that "event" and move on to detecting the next one.
// i.e. we use the return to decide whether to call lvgl.CancelTap();
typedef int (*touchCallback)(globalTouchEvent e);
typedef int (*touchCallback_xy)(uint16_t x, uint16_t y);
Pinetime::Applications::AppControllers* controllers;
typedef struct {
	Pinetime::Applications::AppControllers* controllers;
	touchCallback* tcb;
	touchCallback_xy* tcb_xy;
} setups_t;

touchCallback* tcb; 
touchCallback_xy* tcb_xy;
// ^ pointers to a pointer to a function.hid
// we ALWAYS tell InfiniTime to use these pointer when handling events,
// but we have a dummy handler initially which gets swapped out whenever we actually
// want to handle the events.

lv_color_t fg_colour;
lv_color_t bg_colour;

void init(void* _s)
{
	setups_t* s = (setups_t*) _s;
	controllers = s->controllers;
	tcb = (s->tcb);
	tcb_xy = (s->tcb_xy);
	return;
}

void show_int(int i)
{
	if (i == 0)
		return;

  controllers->brightnessController.Set(Pinetime::Controllers::BrightnessController::Levels::Low);


  lv_obj_t* title = lv_label_create(lv_scr_act(), nullptr);

  char showable[2];
  showable[0] = (char) (48 + i);
  showable[1] = '\0';
  lv_label_set_text(title, showable);

  lv_label_set_align(title, LV_LABEL_ALIGN_CENTER);
  lv_obj_align(title, lv_scr_act(), LV_ALIGN_CENTER, 0, 0);
  lv_obj_set_style_local_text_color(title, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, fg_colour);
}

// set the foreground and background colours for drawing.
void set_colours(uint32_t fg, uint32_t bg)
{
  bg_colour = lv_color_hex(bg);
  fg_colour = lv_color_hex(fg);
}

// places a label centrered at x, y.
void place_label(const char* text, int x, int y)
{
  auto label = lv_label_create(lv_scr_act(), nullptr); // create a label on the active screen
  lv_label_set_text(label, text);
  lv_obj_align(label, nullptr, LV_ALIGN_IN_TOP_LEFT, x, y); // position the label
  lv_obj_set_style_local_text_color(label, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, fg_colour);
}

void set_brightness(brightness_level bl)
{
  switch (bl) {
	  case lo:
	    controllers->brightnessController.Set(Pinetime::Controllers::BrightnessController::Levels::Low);
	  break;
	  case med:
	    controllers->brightnessController.Set(Pinetime::Controllers::BrightnessController::Levels::Medium);
	  break;
	  case hi:
	    controllers->brightnessController.Set(Pinetime::Controllers::BrightnessController::Levels::High);
	  break;
  }
}
void register_global_eventListener(touchCallback e)
{
  *tcb = e;
}
void register_global_eventListener_xy(touchCallback_xy e)
{
  *tcb_xy = e;
}

void disable_sleep()
{
  controllers->systemTask->PushMessage(Pinetime::System::Messages::DisableSleeping);
}

void clear_screen()
{
  lv_obj_clean(lv_scr_act());
  // update the background colour for the current "screen" instance.
  lv_obj_set_style_local_bg_color(lv_scr_act(), LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, bg_colour);
}

void draw_rect(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	// lv_obj_t * rect = lv_obj_create(lv_scr_act(), nullptr);
	// lv_obj_set_size(rect , x2-x1, y2-y1);
	// lv_obj_set_pos(rect , x1, y1);
	// lv_obj_set_style_local_bg_color(rect, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, fg_colour);

	/*
    lv_area_t area;
    area.x1 = x1;
    area.y1 = y1;
    area.x2 = x2;
    area.y2 = y2;

	int bufferSize = (x2-x1+1)*(y2-y1+1);
	lv_color_t* b = (lv_color_t*) std::malloc(sizeof(lv_color_t) * bufferSize);
	std::fill(b, b + bufferSize, fg_colour);

    controllers->lvgl.SetFullRefresh(Pinetime::Components::LittleVgl::FullRefreshDirections::None);
    controllers->lvgl.FlushDisplay(&area, b);

	free(b);
	*/

	if (x1 > 240) x1 = 240;
	if (x2 > 240) x2 = 240;
	if (y1 > 240) y1 = 240;
	if (y2 > 240) y2 = 240;

    lv_area_t area;
    area.x1 = x1;
    area.y1 = y1;
    area.x2 = x1;
    area.y2 = y1;

	lv_color_t b = fg_colour;
	// std::fill(b, b + bufferSize, fg_colour);

    controllers->lvgl.SetFullRefresh(Pinetime::Components::LittleVgl::FullRefreshDirections::None);

	for (int y = y1 ; y < y2 ;  y++)
		for (int x = x1 ; x < x2 ; x++)
		{
			area.x1 = x;
			area.x2 = x;
			area.y1 = y;
			area.y2 = y;
			controllers->lvgl.FlushDisplay(&area, &b);
		}
}

void start_read_hr()
{
    controllers->heartRateController.Start();
}

void stop_read_hr()
{
    controllers->heartRateController.Stop();
}

int get_hr_bpm()
{
	return controllers->heartRateController.HeartRate();
}

void _RefreshTaskCallback(lv_task_t* task) {
  // static_cast<Screen*>(task->user_data)->Refresh();
  timer_interrupt_callback ticb = (timer_interrupt_callback) task->user_data;
  (ticb)();
}

void register_timer_interrupt(timer_interrupt_callback action, int period_ms)
{
	// lv_task_create(Pinetime::Applications::Screens::Screen::RefreshTaskCallback, period_ms, LV_TASK_PRIO_MID, NULL);
	lv_task_create(_RefreshTaskCallback, period_ms, LV_TASK_PRIO_MID, (void*) action);
}
