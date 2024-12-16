#include "compat.h"

/*
int extern_main()
{
	show_int(6);

	return 0;
}
*/

#if true

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

bool isOn = false;
brightness_level brightnessLevel = lo;
bool OnTouchEvent(globalTouchEvent event); // forward declare

void SetColors() {
  int16_t bgColor = isOn ? 0xFF : 0x00 ; // set bgColour according to on or not
  int16_t fgColor = isOn ? 0xB0 : 0xFF ; // set fgColour according to on or not

  set_colours(fgColor, bgColor);
}

void SetIndicators() { // function that updates the indicator visibility according to brightness (not-bright: no indicators, medium-bright: 1 indicator, full-bright: all indicators)

  // left indicator
  place_label("O", 120-8, 120-5);

  // middle indicator
  if (brightnessLevel == hi || brightnessLevel == med)
  { place_label("O", 120, 120-5); }
  else { place_label("o", 120, 120-5); }

  // right indicator
  if (brightnessLevel == hi)
  { place_label("O", 120+8, 120-5); }
  else { place_label("o", 120+8, 120-5); }
}

int extern_main()
{
  set_brightness(lo);

  place_label("i", 120, 120); // display is 240x240 hence we position at 240/2=120 to centre.
  // ^ "i" is my text representation of a flashlight.

  SetIndicators();
  SetColors();

  // systemTask.PushMessage(Pinetime::System::Messages::DisableSleeping);
  disable_sleep();
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
  isOn = !isOn;
  SetColors();
  if (isOn) {
    set_brightness(brightnessLevel); // set brightness using brightness controller
  } else {
    set_brightness(lo); // set brightness using brightness controller
  }
}

bool OnTouchEvent(globalTouchEvent event)
{
  auto SetState = []() {
    if (isOn) {
      set_brightness(brightnessLevel); // set brightness using brightness controller
    }
    SetIndicators(); // update indicators
  };

  if (event == Tap) {
	  Toggle();
	  return true;
  }
  else if (event == SwipeLeft) {
	if (brightnessLevel == hi) 
	{ brightnessLevel = med; }
	else if ( brightnessLevel == med )
	{ brightnessLevel = lo; }
    SetState();
    return true;
  }
  else if (event == SwipeRight) {
	if (brightnessLevel == lo) 
	{ brightnessLevel = med; }
	else if ( brightnessLevel == med )
	{ brightnessLevel = hi; }
    SetState();
    return true;
  }

  return false;
}

#endif

// #####################################################################################

#if false

// #include "displayapp/screens/FlashLight.h"
// #include "displayapp/DisplayApp.h"
// #include "displayapp/screens/Symbols.h"
// #include "displayapp/InfiniTimeTheme.h"

using namespace Pinetime::Applications::Screens;


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

namespace {
/* this event handler is only a performance optimisation; the indirect global event listener works but is slightly slow.
  void EventHandler(lv_obj_t* obj, lv_event_t event) {
    if (event == LV_EVENT_CLICKED) {
      auto* screen = static_cast<FlashLight*>(obj->user_data);
      screen->Toggle();
    }
  }
}
*/

FlashLight::FlashLight(System::SystemTask& systemTask, Controllers::BrightnessController& brightnessController)
  : systemTask {systemTask}, brightnessController {brightnessController} {

  // brightnessController.Set(Controllers::BrightnessController::Levels::Low);
  set_brightness(lo);

  /*
  flashLight = lv_label_create(lv_scr_act(), nullptr); // create a label on the active screen
  lv_obj_set_style_local_text_font(flashLight, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_sys_48);
  lv_label_set_text_static(flashLight, Symbols::flashlight); // set the label to display the flashlight symbol
  lv_obj_align(flashLight, nullptr, LV_ALIGN_CENTER, 0, 0); // centre the label
  */

  // ^ instead of this, we do:
  place_label("i", 120, 120) // display is 240x240 hence we position at 240/2=120 to centre.
  // ^ "i" is my text representation of a flashlight.

  /*
  for (auto& indicator : indicators) { // for each "indicator" (blips that render on the lightbulb icon to indicate flashing)
    indicator = lv_obj_create(lv_scr_act(), nullptr); // create a label on the active screen
    lv_obj_set_size(indicator, 15, 10); // set the label's size
	// ^ so waspOS has no notion of text size hence we dont support text size either cuz compatability.
    lv_obj_set_style_local_border_width(indicator, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 2); // set a border
	// ^ waspOS also doesnt have borders
  }
  */

  /*
  lv_obj_align(indicators[1], flashLight, LV_ALIGN_OUT_BOTTOM_MID, 0, 5); // middle blip
  lv_obj_align(indicators[0], indicators[1], LV_ALIGN_OUT_LEFT_MID, -8, 0); // leftmost blip, slightly rotated
  lv_obj_align(indicators[2], indicators[1], LV_ALIGN_OUT_RIGHT_MID, 8, 0); // rightmost blip, slightly rotated
  */
  // ^ these align the middle blip w.r.t. the flashlight icon, and then the other 2 indicators w.r.t. the middle.
  // instead of this, we just explicitly align them with global x-y positions.
  // not ideal, but it's the most basic form of functionality which we should expect from OSes implementing the compat lib.
  
  // the simpler label positioning from here is now also moved to sinide SetIndactors, since we require positioning and rendering 
  // be done in the same function call to place_label.

  SetIndicators();
  SetColors();

  /* this event handler is only a performance optimisation; the indirect global event listener works but is slightly slow.
  backgroundAction = lv_label_create(lv_scr_act(), nullptr);
  lv_label_set_long_mode(backgroundAction, LV_LABEL_LONG_CROP);
  lv_obj_set_size(backgroundAction, 240, 240);
  lv_obj_set_pos(backgroundAction, 0, 0);
  lv_label_set_text_static(backgroundAction, "");
  lv_obj_set_click(backgroundAction, true);
  backgroundAction->user_data = this;
  lv_obj_set_event_cb(backgroundAction, EventHandler);
  */
  // ^ this is just a big blank square that registers onClick listener.

  systemTask.PushMessage(Pinetime::System::Messages::DisableSleeping);
}

FlashLight::~FlashLight() {
  lv_obj_clean(lv_scr_act());
  lv_obj_set_style_local_bg_color(lv_scr_act(), LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
  systemTask.PushMessage(Pinetime::System::Messages::EnableSleeping);
}

void FlashLight::SetColors() {
  // lv_color_t bgColor = isOn ? LV_COLOR_WHITE : LV_COLOR_BLACK; // set bgColour according to on or not
  // lv_color_t fgColor = isOn ? Colors::lightGray : LV_COLOR_WHITE; // set fgColour according to on or not
  int16_t bgColor = isOn ? 0xFFFFFF : 0x000000 ; // set bgColour according to on or not
  int16_t fgColor = isOn ? 0xB0B0B0 : 0xFFFFFF ; // set fgColour according to on or not

  /*
  lv_obj_set_style_local_bg_color(lv_scr_act(), LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, bgColor); // set the background colour for the current "screen" instance.
  lv_obj_set_style_local_text_color(flashLight, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, fgColor); // set the text colour for the "flashlight" label (which is actually a symbol)
  for (auto& indicator : indicators) { // set colours of all the indicators. (visible fg, invisible bg, borderColour = fgColour)
    lv_obj_set_style_local_bg_color(indicator, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, fgColor);
    lv_obj_set_style_local_bg_color(indicator, LV_OBJ_PART_MAIN, LV_STATE_DISABLED, bgColor);
    lv_obj_set_style_local_border_color(indicator, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, fgColor);
  }
  */
  // ^ this sets colours for various individual items, but since we use re-draws and global colours, we dont need to do all of that.

  set_colours(fgColor, bgColor);
}

void FlashLight::SetIndicators() { // function that updates the indicator visibility according to brightness (not-bright: no indicators, medium-bright: 1 indicator, full-bright: all indicators)
  // using namespace Pinetime::Controllers;

  /*
  if (brightnessLevel == BrightnessController::Levels::High) {
    lv_obj_set_state(indicators[1], LV_STATE_DEFAULT); // show indicator
    lv_obj_set_state(indicators[2], LV_STATE_DEFAULT); // show indicator
  } else if (brightnessLevel == BrightnessController::Levels::Medium) {
    lv_obj_set_state(indicators[1], LV_STATE_DEFAULT); // show indicator
    lv_obj_set_state(indicators[2], LV_STATE_DISABLED); // hide indicator
  } else {
    lv_obj_set_state(indicators[1], LV_STATE_DISABLED); // hide indicator
    lv_obj_set_state(indicators[2], LV_STATE_DISABLED); // hide indicator
  }
  */
  // ^ this code varies how many indicators are visible according to how strong the brightness is.
  // since we dont have label borders and hence cant use this trick, we just use different sized Os instead.

  // left indicator
  place_label("O", 120-8, 120-5)

  // middle indicator
  if (brightnessLevel == BrightnessController::Levels::High || brightnessLevel == BrightnessController::Levels::High)
  { place_label("O", 120, 120-5) }
  else { place_label("o", 120, 120-5) }

  // right indicator
  if (brightnessLevel == BrightnessController::Levels::High)
  { place_label("O", 120+8, 120-5) }
  else { place_label("o", 120+8, 120-5) }
}

void FlashLight::Toggle() {
  isOn = !isOn;
  SetColors();
  if (isOn) {
    // brightnessController.Set(brightnessLevel); // set brightness using brightness controller
    set_brightness(brightnessLevel); // set brightness using brightness controller
  } else {
    // brightnessController.Set(Controllers::BrightnessController::Levels::Low); // set brightness using brightness controller
    set_brightness(brightness_level::low); // set brightness using brightness controller
  }
}

/*
bool FlashLight::OnTouchEvent(Pinetime::Applications::TouchEvents event) { // whenever a touch event happens...
  using namespace Pinetime::Controllers;

  auto SetState = [this]() {
    if (isOn) {
      // brightnessController.Set(brightnessLevel); // set brightness using brightness controller
      set_brightness(brightnessLevel); // set brightness using brightness controller
    }
    SetIndicators(); // update indicators
  };

  if (event == TouchEvents::Tap) { // whenever a left swipe event happens... decrement brightness
	Toggle();
    return true;
  }
  if (event == TouchEvents::SwipeLeft) { // whenever a left swipe event happens... decrement brightness
    if (brightnessLevel == BrightnessController::Levels::High) {
      brightnessLevel = BrightnessController::Levels::Medium;
      SetState();
    } else if (brightnessLevel == BrightnessController::Levels::Medium) {
      brightnessLevel = BrightnessController::Levels::Low;
      SetState();
    }
    return true;
  }
  if (event == TouchEvents::SwipeRight) { // whenever a right swipe event happens... increment brightness
    if (brightnessLevel == BrightnessController::Levels::Low) {
      brightnessLevel = BrightnessController::Levels::Medium;
      SetState(); // update GUI to reflect our changes
    } else if (brightnessLevel == BrightnessController::Levels::Medium) {
      brightnessLevel = BrightnessController::Levels::High;
      SetState(); // update GUI to reflect our changes
    }
    return true;
  }

  return false;
}
*/
// ^ this whole function is replaced by the following:
bool FlashLight::OnTouchEvent(globalTouchEvent event)
{
  auto SetState = [this]() {
    if (isOn) {
      // brightnessController.Set(brightnessLevel); // set brightness using brightness controller
      set_brightness(brightnessLevel); // set brightness using brightness controller
    }
    SetIndicators(); // update indicators
  };

  if (event == Tap) {
	  Toggle();
	  return true;
  }
  else if (event == SwipeLeft) {
	if (brightness_level == hi) 
	{ brightness_level = med }
	else if ( brightness_level == med )
	{ brightness_level = lo; }
    SetState();
    return true;
  }
  else if (event == SwipeRight) {
	if (brightness_level == lo) 
	{ brightness_level = med }
	else if ( brightness_level == med )
	{ brightness_level = hi; }
    SetState();
    return true;
  }

  return false;
}

#endif
