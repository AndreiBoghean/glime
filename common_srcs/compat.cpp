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
#include <lvgl/lvgl.h>
#include <string>

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

touchCallback* tcb; // a pointer to a pointer to a function.
					 // we ALWAYS tell InfiniTime to use this pointer when handling events,
					 // but we have a dummy handler initially which gets swapped out whenever we actually
					 // want to handle the events.
touchCallback_xy* tcb_xy;
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

  char numba = (char) (48 + i);
  lv_label_set_text(title, &numba);

  lv_label_set_align(title, LV_LABEL_ALIGN_CENTER);
  lv_obj_align(title, lv_scr_act(), LV_ALIGN_CENTER, 0, 0);

}

// set the foreground and background colours for drawing.
lv_color_t fg_colour;
lv_color_t bg_colour;
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
void register_global_eventListener(touchCallback_xy e)
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
