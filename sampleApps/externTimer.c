#include "compat.h"
#include "stdint.h"

// forward declares
void ToggleRunning();
void Reset();
void SetTimerRunning();
void SetTimerStopped();
void DisplayTime();
void Refresh();

void btnEventHandler(enum buttonTouchEvent event) {
  if (event == buttonTouchEvent::btn_shortClick) {
	ToggleRunning();
  } else if (event == buttonTouchEvent::btn_longPress || event == buttonTouchEvent::btn_longPressRepeat) {
	Reset();
  }
}

void* timerObj = nullptr;
void* minCounter;
void* secCounter;
int extern_main() {
  set_colours(0xff00ff, 0x000000); // TODO: you've still not fixed the default-text-colour-is-black issue smh
  place_label(":", 120, 120);

  minCounter = counter_create(0, 0, 59, 120-60, 110);
  secCounter = counter_create(10, 0, 59, 120+60, 110);
  counter_render(minCounter);
  counter_render(secCounter);

  // TODO: create place_button
  place_button(btnEventHandler, 120, 220);

  // place text of play/pause button
  place_label("start", 120, 220);

  timerObj = timer_create(Reset, 0);

  // ok here is first hurdle.
  // we do not want to be given data from mr abstraction.
  // what if we check that the timer object is enabled?
  if (timer_isRunning(timerObj)) SetTimerRunning();
  else SetTimerStopped();

  register_timer_interrupt(Refresh, 30); // display refreshes every 30ms.

  return 0;
}

void MaskReset() {
  if (!timer_isRunning(timerObj)) place_label("startM", 120, 210);
}

void Refresh() {
  if (timer_isRunning(timerObj)) DisplayTime();
}

void DisplayTime() {
  int displaySeconds = timer_msRemaining(timerObj) / 1000; // TOCO: implement in compat
  counter_set(minCounter, displaySeconds / 60);
  counter_set(secCounter, displaySeconds % 60);
}

void SetTimerRunning() {
  place_label("Pause", 120, 220);
}

void SetTimerStopped() {
  place_label("Start", 120, 220);
}

void ToggleRunning() {
  int secVal = counter_get(secCounter);
  int minVal = counter_get(minCounter);
  if (timer_isRunning(timerObj)) {
	  place_label("running", 120, 70);
	  DisplayTime();
	  timer_stop(timerObj);
	  SetTimerStopped();
  }
  else if (secVal + minVal > 0) {
	  place_label("walking", 120, 120);
	  timer_setPeriod(timerObj, (minVal*60 + secVal) * 1000); // in miliseconds
	  timer_start(timerObj);
	  Refresh();
	  SetTimerRunning();
  }
}

void Reset() {
  DisplayTime();
  SetTimerStopped();
}
