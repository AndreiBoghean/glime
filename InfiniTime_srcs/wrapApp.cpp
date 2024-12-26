#include "displayapp/screens/wrapApp.h"
#include "displayapp/screens/externApp.h"

#include "compat.h"

using namespace Pinetime::Applications::Screens;

typedef struct {
	Pinetime::Applications::AppControllers* controllers;
	touchCallback* tcb;
	touchCallback_xy* tcb_xy;
} setups_t;

wrapApp::wrapApp(AppControllers& controllers) {
  setups_t setups = {&controllers, &tcb, &tcb_xy};
  init((void*) &setups);
  extern_main();

  // lv_obj_t* title = lv_label_create(lv_scr_act(), nullptr);
  // lv_label_set_text_static(title, "My test application");
  // lv_label_set_align(title, LV_LABEL_ALIGN_CENTER);
  // lv_obj_align(title, lv_scr_act(), LV_ALIGN_CENTER, 0, 0);
}

int wrapApp::default_OnTouchEvent(globalTouchEvent event)
{
  if (event != SwipeRight) { return 1; }

  lv_obj_t* title = lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_text_static(title, "My test application");
  lv_label_set_align(title, LV_LABEL_ALIGN_CENTER);
  lv_obj_align(title, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, 0, 0);

  return 1;
}

int wrapApp::default_OnTouchEvent_xy(uint16_t x, uint16_t y)
{
	if (x == 0) return 0;
	if (y == 0) return 0;
	return 0;
}

bool wrapApp::OnTouchEvent(Pinetime::Applications::TouchEvents event)
{
  switch (event) {
    case TouchEvents::Tap:
	    return tcb(Tap) == 1;
	  break;
    case TouchEvents::DoubleTap:
	    return tcb(TapDouble) == 1;
	  break;
    case TouchEvents::LongTap:
	    return tcb(TapLong) == 1;
	  break;
    case TouchEvents::SwipeLeft:
	    return tcb(SwipeLeft) == 1;
	  break;
    case TouchEvents::SwipeRight:
	    return tcb(SwipeRight) == 1;
	  break;
    case TouchEvents::SwipeUp:
	    return tcb(SwipeUp) == 1;
	  break;
    case TouchEvents::SwipeDown:
	    return tcb(SwipeDown) == 1;
	  break;
	default:
	  return false;
	  break;
  }
  return true;
}

bool wrapApp::OnTouchEvent(uint16_t x, uint16_t y)
{
	return tcb_xy(x, y) == 1;
}

wrapApp::~wrapApp() {
  lv_obj_clean(lv_scr_act());
}
