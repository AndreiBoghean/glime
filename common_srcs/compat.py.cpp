#include "compat.h"
#include "py/runtime.h"
#include "py/misc.h" // memory allocation is in misc for some reason lol

mp_obj_t draw_string_callback;

void init(void* _draw_string_callback)
{
	draw_string_callback = * ((mp_obj_t*) _draw_string_callback);
}

void make_label(char *text)
{
	if (text)
		return;
}

void show_int(int i)
{
	mp_obj_t* args = m_new(mp_obj_t, 5);
	char numba = (char) (48 + i);

	args[0] = mp_obj_new_str(&numba, 1); // string
	args[1] = mp_obj_new_int(0); // x
	args[2] = mp_obj_new_int(108); // y
	args[3] = mp_obj_new_int(240); // width
	args[4] = mp_obj_new_bool(0); // right justify?
								  //
	mp_call_function_n_kw(draw_string_callback, 5, 0, args);
	m_del(mp_obt_t, args, 5);
}
