#include "py/obj.h"
#include "py/runtime.h"
#include "externApp.h"
#include "compat.h"

touchCallback tcb;
touchCallback_xy tcb_xy;
mp_obj_t touch_handler(mp_obj_t py_eventID, mp_obj_t py_x, mp_obj_t py_y)
{
	int eventID = mp_obj_get_int(py_eventID);
	int x = mp_obj_get_int(py_x);
	int y = mp_obj_get_int(py_y);
	switch (eventID) {
		case -1:
    		// return mp_obj_new_str("unimpl event", strlen("unimpl event")); // create py string
		break;
		case 0:
    		// return mp_obj_new_str("zero", strlen("zero")); // create py string
			tcb(Tap);
			tcb_xy(x, y);
		break;
		case 3:
    		// return mp_obj_new_str("tree", strlen("tree")); // create py string
			tcb(SwipeLeft);
		break;
		case 4:
    		// return mp_obj_new_str("floor", strlen("floor")); // create py string
			tcb(SwipeRight);
		break;
	}

	return mp_const_none;
}

typedef struct {
	mp_obj_t delegator;
	touchCallback* tcb;
} setups_t;

STATIC mp_obj_t gateway_handle_main(mp_obj_t delegator) {
	setups_t setups = {delegator, &tcb, &tcb_xy};
	init((void*) &setups);
	extern_main();

	return mp_const_none;
}

// bind our (1 argument) function name to a new "gateway_XMHlet_obj" python object
STATIC MP_DEFINE_CONST_FUN_OBJ_1(gateway_mainer_obj, gateway_handle_main);
STATIC MP_DEFINE_CONST_FUN_OBJ_1(touch_handler_obj, touch_handler);

// bind objects 4 stuff to python names 4 stuff
STATIC const mp_rom_map_elem_t gateway_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_gateway) },
    { MP_ROM_QSTR(MP_QSTR_handle_main), MP_ROM_PTR(&gateway_mainer_obj) },
    { MP_ROM_QSTR(MP_QSTR_touch_handler), MP_ROM_PTR(&touch_handler_obj) },
};


STATIC MP_DEFINE_CONST_DICT(gateway_module_globals, gateway_module_globals_table);

const mp_obj_module_t gateway_user_cmodule = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&gateway_module_globals,
};

MP_REGISTER_MODULE(MP_QSTR_gateway, gateway_user_cmodule, MODULE_GATEWAY_ENABLED);
