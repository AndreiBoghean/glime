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

#if 1
#include "displayapp/screens/Timer.h"
#include "displayapp/screens/Screen.h"
#include "displayapp/screens/Symbols.h"
#include "displayapp/InfiniTimeTheme.h"
#include <lvgl/lvgl.h>

using namespace Pinetime::Applications::Screens;

static void btnEventHandler(lv_obj_t* obj, lv_event_t event) {
  auto* screen = static_cast<Timer*>(obj->user_data);
  if (event == LV_EVENT_PRESSED) {
    screen->ButtonPressed();
  } else if (event == LV_EVENT_RELEASED || event == LV_EVENT_PRESS_LOST) {
    screen->MaskReset();
  } else if (event == LV_EVENT_SHORT_CLICKED) {
    screen->ToggleRunning();
  }
}


int minuteVal = 0;
int secondVal = 0;

void incrMinute() { minuteVal++; }
void decrMinute() { minuteVal--; }
void incrSecond() { secondVal++; }
void decrSecond() { secondVal--; }

Timer::Timer(Controllers::Timer& timerController) : timer {timerController} {

  place_label(":", 120, 120);
  // lv_obj_t* colonLabel = lv_label_create(lv_scr_act(), nullptr);
  // lv_obj_set_style_local_text_font(colonLabel, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &jetbrains_mono_76);
  // lv_obj_set_style_local_text_color(colonLabel, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
  // lv_label_set_text_static(colonLabel, ":");
  // lv_obj_align(colonLabel, lv_scr_act(), LV_ALIGN_CENTER, 0, -29);

  // TODO: create place_counter
  counter* minCounter = place_counter("00", 120-60, 120);
  counter* secCounter = place_counter("00", 120+60, 120);
  // minuteCounter.Create();
  // secondCounter.Create();
  // lv_obj_align(minuteCounter.GetObject(), nullptr, LV_ALIGN_IN_TOP_LEFT, 0, 0);
  // lv_obj_align(secondCounter.GetObject(), nullptr, LV_ALIGN_IN_TOP_RIGHT, 0, 0);

  // mask stuff; not needed?
  /*
  highlightObjectMask = lv_objmask_create(lv_scr_act(), nullptr);
  lv_obj_set_size(highlightObjectMask, 240, 50);
  lv_obj_align(highlightObjectMask, lv_scr_act(), LV_ALIGN_IN_BOTTOM_MID, 0, 0);

  lv_draw_mask_line_param_t tmpMaskLine;

  lv_draw_mask_line_points_init(&tmpMaskLine, 0, 0, 0, 240, LV_DRAW_MASK_LINE_SIDE_LEFT);
  highlightMask = lv_objmask_add_mask(highlightObjectMask, &tmpMaskLine);

  lv_obj_t* btnHighlight = lv_obj_create(highlightObjectMask, nullptr);
  lv_obj_set_style_local_radius(btnHighlight, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, LV_RADIUS_CIRCLE);
  lv_obj_set_style_local_bg_color(btnHighlight, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_ORANGE);
  lv_obj_set_size(btnHighlight, LV_HOR_RES, 50);
  lv_obj_align(btnHighlight, lv_scr_act(), LV_ALIGN_IN_BOTTOM_MID, 0, 0);
  */

  // mask stuff; not needed?
  // btnObjectMask = lv_objmask_create(lv_scr_act(), nullptr);
  // lv_obj_set_size(btnObjectMask, 240, 50);
  // lv_obj_align(btnObjectMask, lv_scr_act(), LV_ALIGN_IN_BOTTOM_MID, 0, 0);

  // mask stuff; not needed?
  /*
  lv_draw_mask_line_points_init(&tmpMaskLine, 0, 0, 0, 240, LV_DRAW_MASK_LINE_SIDE_RIGHT);
  btnMask = lv_objmask_add_mask(btnObjectMask, &tmpMaskLine);
  */

  // place play/pause button
  place_button(btnEventHandler, 60, 180); // TODO: implement in compat
  // btnPlayPause = lv_btn_create(btnObjectMask, nullptr);
  // btnPlayPause->user_data = this;
  // lv_obj_set_style_local_radius(btnPlayPause, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, LV_RADIUS_CIRCLE);
  // lv_obj_set_style_local_bg_color(btnPlayPause, LV_BTN_PART_MAIN, LV_STATE_DEFAULT, Colors::bgAlt);
  // lv_obj_set_event_cb(btnPlayPause, btnEventHandler);
  // lv_obj_set_size(btnPlayPause, LV_HOR_RES, 50);

  // place text of play/pause button
  place_text("start", 60, 180);
  // txtPlayPause = lv_label_create(lv_scr_act(), nullptr);
  // lv_obj_align(txtPlayPause, btnPlayPause, LV_ALIGN_CENTER, 0, 0);

  // ok here is first hurdle.
  // we do not want to be given data from mr abstraction.
  // what if we check that the timer object is enabled?
  if (timer_is_running(timerObj)) SetTimerRunning(); // TODO: implement in compat
  else SetTimerStopped();
  // if (timer.IsRunning()) {
  //   SetTimerRunning();
  // } else {
  //   SetTimerStopped();
  // }

  register_timer_interrupt(RefreshTaskCallback, 30);
  // taskRefresh = lv_task_create(RefreshTaskCallback, LV_DISP_DEF_REFR_PERIOD, LV_TASK_PRIO_MID, this);
}

// memory management? lol no ur crazy get out of here
// Timer::~Timer() {
//   lv_task_del(taskRefresh);
//   lv_obj_clean(lv_scr_act());
// }

void Timer::ButtonPressed() {
  pressTime = get_current_system_tick(); // TODO: implement in compat
  // pressTime = xTaskGetTickCount();

  buttonPressing = true;
}

void Timer::MaskReset() {
  buttonPressing = false;

  if (!timer_is_running(timerObj)) place_text("start", 60, 180);

  // A click event is processed before a release event,
  // so the release event would override the "Pause" text without this check
  // if (!timer.IsRunning()) {
  //   lv_label_set_text_static(txtPlayPause, "Start");
  // }
  
  // mask stuff; not needed?
  // maskPosition = 0;
  // UpdateMask();
}

// mask stuff; not needed?
// void Timer::UpdateMask() {
//   lv_draw_mask_line_param_t maskLine;
// 
//   lv_draw_mask_line_points_init(&maskLine, maskPosition, 0, maskPosition, 240, LV_DRAW_MASK_LINE_SIDE_LEFT);
//   lv_objmask_update_mask(highlightObjectMask, highlightMask, &maskLine);
// 
//   lv_draw_mask_line_points_init(&maskLine, maskPosition, 0, maskPosition, 240, LV_DRAW_MASK_LINE_SIDE_RIGHT);
//   lv_objmask_update_mask(btnObjectMask, btnMask, &maskLine);
// }

void Timer::Refresh() {
  if (timer_is_running(timerObj)) DisplayTime(); // TODO: implement in compat
  // this code is used for the reset function, which we're ignoring for now. TODO: leave space for future extension to serve long press events on button handlers
  // else if (buttonPressing && get_current_system_tick() > pressTime + ms_to_sysTicks(150)) // if the button has been pressed long enough...
  //  place_text("reset", 60, 180);

  // if (timer.IsRunning()) {
  //   DisplayTime();
  // } else if (buttonPressing && xTaskGetTickCount() > pressTime + pdMS_TO_TICKS(150)) {
  //   lv_label_set_text_static(txtPlayPause, "Reset");
  //   // mask stuff; not needed?
  //   // maskPosition += 15;
  //   // if (maskPosition > 240) {
  //   //   MaskReset();
  //   //   Reset();
  //   // } else {
  //   //   UpdateMask();
  //   // }
  // }
}

void Timer::DisplayTime() {
  displaySeconds = timer_seconds_remaining(timerObj); // TOCO: implement in compat
  counter_set(minCounter, displaySeconds / 60);
  counter_set(secCounter, displaySeconds % 60);


  // displaySeconds = std::chrono::duration_cast<std::chrono::seconds>(timer.GetTimeRemaining());
  // if (displaySeconds.IsUpdated()) {
  //   minuteCounter.SetValue(displaySeconds.Get().count() / 60);
  //   secondCounter.SetValue(displaySeconds.Get().count() % 60);
  // }
}

void Timer::SetTimerRunning() {
  place_label("Pause", 60, 180);


  // minuteCounter.HideControls();
  // secondCounter.HideControls();
  // lv_label_set_text_static(txtPlayPause, "Pause");
}

void Timer::SetTimerStopped() {
  place_label("Start", 60, 180);


  // minuteCounter.ShowControls();
  // secondCounter.ShowControls();
  // lv_label_set_text_static(txtPlayPause, "Start");
}

void Timer::ToggleRunning() {
  if (timer_isRunning(timerObj)) {
	  DisplayTime();
	  timer_stop(timerObj);
	  SetTimerStopped();
  }

  int secVal = counter_getVal(secCounter);
  int minVal = counter_getVal(minCounter);
  else if (secVal + minVal > 0) {
	  timer_setPeriod(timerObj, (minVal*60 + secVal) * 1000); // in miliseconds
	  timer_start(timerObj);
	  Refresh();
	  SetTimerRunning();
  }

  // if (timer.IsRunning()) {
  //   DisplayTime();
  //   timer.StopTimer();
  //   SetTimerStopped();
  // } else if (secondCounter.GetValue() + minuteCounter.GetValue() > 0) {
  //   auto timerDuration = std::chrono::minutes(minuteCounter.GetValue()) + std::chrono::seconds(secondCounter.GetValue());
  //   timer.StartTimer(timerDuration);
  //   Refresh();
  //   SetTimerRunning();
  // }
}

void Timer::Reset() {
  DisplayTime();
  SetTimerStopped();
}

#endif
