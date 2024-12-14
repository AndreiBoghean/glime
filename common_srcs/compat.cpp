#include "compat.h"
#include "src/displayapp/screens/Screen.h"

#include "src/components/brightness/BrightnessController.h"
#include "src/displayapp/Controllers.h"

Pinetime::Applications::AppControllers* controllers;
void init(void* setups)
{
	controllers = ((Pinetime::Applications::AppControllers*) setups);
	return;
}

void make_label(char *text)
{
	if (text)
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
