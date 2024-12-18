#include "compat.h"

///*
int extern_main()
{
	show_int(6);

	return 0;
}
//*/

/*
 * labels, arbitrarily positioned and rotated, with arbitrary SVG displaying. (rip lol)
 * concern: displaying icons may be hard; restrict to text only, with images as a stretch goal?
 * ^ I say this because image support may need to be independnetly implemented, via some tool that converts an image to the respective format for an OS.
 * symbols must be colour-able.
 * symbol visility must be toggle-able
 * symbols can have a foreground, background, and border colour
 *
 * set brightness via brightness controllerk.cpp:#include "displayapp/TouchEvents.h"
systemtask/SystemTask.cpp:                gesture != Pinetime::Applications::TouchEvents::None &&
systemtask/SystemTask.cpp:                ((gesture == Pinetime::Applications::TouchEvents::DoubleTap &&
systemtask/SystemTask.cpp:
 *     - maybe enum, maybe int?
 * touch event listener, left swipe event, right swipe event
*/

#if false
int isOn = 0;
enum brightness_level brightnessLevel = lo;
int OnTouchEvent(enum globalTouchEvent event); // forward declare

void SetColors() {
  uint32_t bgColor = isOn ? 0xFFFFFF : 0x000000 ; // set bgColour according to on or not
  uint32_t fgColor = isOn ? 0xB0B0B0 : 0xFFFFFF ; // set fgColour according to on or not

  set_colours(fgColor, bgColor);
}

void SetIndicators() { // function that updates the indicator visibility according to brightness (not-bright: no indicators, medium-bright: 1 indicator, full-bright: all indicators)

  place_label("i", 120, 120+20); // display is 240x240 hence we position at 240/2=120 to centre.
  // ^ "i" is my text representation of a flashlight. TODO: support image icons

  // left indicator
  place_label("O", 120-8*2, 120-5*2);

  // middle indicator
  if (brightnessLevel == hi || brightnessLevel == med)
  { place_label("O", 120, 120-5*2); }
  else { place_label("o", 120, 120-5*2); }

  // right indicator
  if (brightnessLevel == hi)
  { place_label("O", 120+8*2, 120-5*2); }
  else { place_label("o", 120+8*2, 120-5*2); }
}

int extern_main()
{
  set_brightness(lo);

  SetColors();
  SetIndicators();

  // systemTask.PushMessage(Pinetime::System::Messages::DisableSleeping);
  // disable_sleep();
  register_global_eventListener(OnTouchEvent);
  return 0;
}

/* TODO: convert this destructor.
FlashLight::~FlashLight() {
  lv_obj_clean(lv_scr_act());
  lv_obj_set_style_local_bg_color(lv_scr_act(), LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
  systemTask.PushMessage(Pinetime::System::Messages::EnableSleeping);
}
*/

void Toggle() {
  isOn = 1-isOn;
  SetColors();
  if (isOn) {
    set_brightness(brightnessLevel); // set brightness using brightness controller
  } else {
    set_brightness(lo); // set brightness using brightness controller
  }
}

int OnTouchEvent(enum globalTouchEvent event)
{
  clear_screen(); // prepare for drawing the next screen state.

  if (event == Tap) {
	  Toggle();
	  if (isOn) {
	    set_brightness(brightnessLevel); // set brightness using brightness controller
	  }
	  SetIndicators(); // update indicators
	  return 1;
  }
  else if (event == SwipeLeft) {
	if (brightnessLevel == hi) 
	{ brightnessLevel = med; }
	else if ( brightnessLevel == med )
	{ brightnessLevel = lo; }

	if (isOn) {
	  set_brightness(brightnessLevel); // set brightness using brightness controller
	}
	SetIndicators(); // update indicators
					 //
    return 1;
  }
  else if (event == SwipeRight) {
	if (brightnessLevel == lo) 
	{ brightnessLevel = med; }
	else if ( brightnessLevel == med )
	{ brightnessLevel = hi; }

	if (isOn) {
	  set_brightness(brightnessLevel); // set brightness using brightness controller
	}
	SetIndicators(); // update indicators
					 //
    return 1;
  }

  return 0;
}
#endif
