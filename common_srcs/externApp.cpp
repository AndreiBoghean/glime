#include "compat.h"
#include "stdint.h"

#if 0
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
#endif

#if 1
// #include "displayapp/screens/Timer.h"
// #include "displayapp/screens/Screen.h"
// #include "displayapp/screens/Symbols.h"
// #include "displayapp/InfiniTimeTheme.h"
// #include <lvgl/lvgl.h>

// forward declares
void ToggleRunning();
void Reset();
void SetTimerRunning();
void SetTimerStopped();
void DisplayTime();
void Refresh();

void btnEventHandler(enum buttonTouchEvent event) {
  if (event == buttonTouchEvent::btn_shortClick) {
    // screen->ToggleRunning();
	ToggleRunning();
  } else if (event == buttonTouchEvent::btn_longPress || event == buttonTouchEvent::btn_longPressRepeat) {
    // screen->Reset();
	Reset();
  }
}

// Timer::Timer(Controllers::Timer& timerController) : timer {timerController} {
void* timerObj = nullptr;
void* minCounter;
void* secCounter;
int extern_main() {
  set_colours(0xff00ff, 0x000000); // TODO: you've still not fixed the default-text-colour-is-black issue smh
  // place_label(":", 120, 120);

  minCounter = counter_create(42, 0, 59, 120-60, 110);
  secCounter = counter_create(42, 0, 59, 120+60, 110);
  counter_render(minCounter);
  counter_render(secCounter);

  // TODO: create place_button
  place_button(btnEventHandler, 120, 220);

  // place text of play/pause button
  place_label("start", 120, 220);

  return 0;

  if (timerObj == nullptr) {
    timerObj = timer_create(Reset, 0);
  }

  // ok here is first hurdle.
  // we do not want to be given data from mr abstraction.
  // what if we check that the timer object is enabled?
  if (timer_isRunning(timerObj)) SetTimerRunning(); // TODO: implement in compat
  else SetTimerStopped();
  // if (timer.IsRunning()) {
  //   SetTimerRunning();
  // } else {
  //   SetTimerStopped();
  // }

  register_timer_interrupt(Refresh, 30); // display refreshes every 30 seconds.
  // taskRefresh = lv_task_create(RefreshTaskCallback, LV_DISP_DEF_REFR_PERIOD, LV_TASK_PRIO_MID, this);
}

void MaskReset() {
  if (!timer_isRunning(timerObj)) place_label("start", 60, 180);

  // A click event is processed before a release event,
  // so the release event would override the "Pause" text without this check
  // if (!timer.IsRunning()) {
  //   lv_label_set_text_static(txtPlayPause, "Start");
  // }
}

void Refresh() {
  if (true || timer_isRunning(timerObj)) DisplayTime(); // TODO: implement in compat
  // this code is used for the reset function, which we're ignoring for now. TODO: leave space for future extension to serve long press events on button handlers
  // else if (buttonPressing && get_current_system_tick() > pressTime + ms_to_sysTicks(150)) // if the button has been pressed long enough...
  //  reset();
}

void DisplayTime() {
  int displaySeconds = timer_secsRemaining(timerObj); // TOCO: implement in compat
  counter_set(minCounter, displaySeconds / 60);
  counter_set(secCounter, displaySeconds % 60);
}

void SetTimerRunning() {
  place_label("Pause", 60, 180);

  // minuteCounter.HideControls();
  // secondCounter.HideControls();
  // lv_label_set_text_static(txtPlayPause, "Pause");
}

void SetTimerStopped() {
  place_label("Start", 60, 180);


  // minuteCounter.ShowControls();
  // secondCounter.ShowControls();
  // lv_label_set_text_static(txtPlayPause, "Start");
}

void ToggleRunning() {
  int secVal = counter_get(secCounter);
  int minVal = counter_get(minCounter);
  if (timer_isRunning(timerObj)) {
	  DisplayTime();
	  timer_stop(timerObj);
	  SetTimerStopped();
  }
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

void Reset() {
  DisplayTime();
  SetTimerStopped();
}

#endif
