#include "compat.h"
#include "py/runtime.h"
#include "py/misc.h" // memory allocation is in misc for some reason lol
#include "string.h"

STATIC mp_obj_t delegate;
touchCallback* tcb_pointer;

typedef struct {
	mp_obj_t delegator;
	touchCallback* tcb_pointer;
} setups_t;

void init(void* _setupts)
{
	setups_t* setups = (setups_t*) _setupts;
	delegate = setups->delegator;
	tcb_pointer = setups->tcb_pointer;
}

void make_label(char *text)
{
	if (text)
		return;
}

void show_int(int i)
{
    mp_obj_t* instr = mp_obj_new_str("show_int", strlen("show_int")); // create py string

	mp_obj_t* args = m_new(mp_obj_t, 2);
	args[0] = instr;
	args[1] = mp_obj_new_int(i); // options;

    mp_call_function_n_kw(delegate, 2, 0, args);
    m_del(args, args, 2); // delete args object
}

// places a label centrered at x, y.
void place_label(const char* text, int x, int y)
{
    mp_obj_t* instr = mp_obj_new_str("place_label", strlen("place_label")); // create py string

	mp_obj_t* args = m_new(mp_obj_t, 4);
	args[0] = instr;
    args[1]  = mp_obj_new_str(text, strlen(text));
	args[2] = mp_obj_new_int(x);
	args[3] = mp_obj_new_int(y);

    mp_call_function_n_kw(delegate, 4, 0, args);
    m_del(args, args, 4); // delete args object
}

void set_colours(uint32_t fg, uint32_t bg)
{
    mp_obj_t* instr = mp_obj_new_str("set_colours", strlen("set_colours")); // create py string

	mp_obj_t* args = m_new(mp_obj_t, 3);
	args[0] = instr;
	args[1] = mp_obj_new_int(fg);
	args[2] = mp_obj_new_int(bg);

    mp_call_function_n_kw(delegate, 3, 0, args);
    m_del(args, args, 3); // delete args object
}
// set the foreground and background colours for drawing.

void set_brightness(enum brightness_level bl)
{
    mp_obj_t* instr = mp_obj_new_str("set_brightness", strlen("set_brightness")); // create py string

	mp_obj_t* args = m_new(mp_obj_t, 2);
	args[0] = instr;
	args[1] = mp_obj_new_int(bl);

    mp_call_function_n_kw(delegate, 2, 0, args);
    m_del(args, args, 2); // delete args object
}

void register_global_eventListener(touchCallback e)
{
  *tcb_pointer = e;
}
// ^ callback returns a boolean according to whether it actioned on the event or not
// if it DID action, then we finalise that "event" and move on to detecting the next one.
// i.e. we use the return to decide whether to call lvgl.CancelTap();

void disable_sleep()
{

}

void clear_screen()
{
    mp_obj_t* instr = mp_obj_new_str("clear_screen", strlen("clear_screen")); // create py string

	mp_obj_t* args = m_new(mp_obj_t, 1);
	args[0] = instr;

    mp_call_function_n_kw(delegate, 1, 0, args);
    m_del(args, args, 1); // delete args object
}
