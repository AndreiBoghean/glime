#include "compat.h"
#include "py/runtime.h"
#include "py/misc.h" // memory allocation is in misc for some reason lol
#include "string.h"

mp_obj_t delegate;

void init(void* _delegate)
{
	delegate = * ((mp_obj_t*) _delegate);
}

void make_label(char *text)
{
	if (text)
		return;
}

void show_int(int i)
{
    mp_obj_t* instr = mp_obj_new_str("show_int", strlen("show_int")); // string
															  //
    // mp_obj_t* options = m_new(mp_obj_t, 1);
    // options[0] = mp_obj_new_int(i);

	mp_obj_t* args = m_new(mp_obj_t, 2);
	args[0] = instr;
	args[1] = mp_obj_new_int(i); // options;

    mp_call_function_n_kw(delegate, 2, 0, args);
    // mp_call_function_2(delegate, instr, options);
    m_del(args, args, 2); // delete args object
}

// places a label centrered at x, y.
void place_label(const char* text, int x, int y)
{

  if (text) return;
  if (x) return;
  if (y) return;
}

void set_colours(uint32_t fg, uint32_t bg)
{
  if (fg) return;
  if (bg) return;
}
// set the foreground and background colours for drawing.

void set_brightness(enum brightness_level bl)
{
  if (bl) return;
}

void register_global_eventListener(touchCallback e)
{
  if (e) return;
}
// ^ callback returns a boolean according to whether it actioned on the event or not
// if it DID action, then we finalise that "event" and move on to detecting the next one.
// i.e. we use the return to decide whether to call lvgl.CancelTap();

void disable_sleep()
{

}

void clear_screen()
{

}
