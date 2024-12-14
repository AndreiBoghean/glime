#include "py/obj.h"
#include "py/runtime.h"
#include "externApp.h"
#include "compat.h"

STATIC mp_obj_t gateway_handle_main(mp_obj_t draw_string_callback) {
	init(&draw_string_callback);
	extern_main();
}

// bind our (1 argument) function name to a new "gateway_XMHlet_obj" python object
STATIC MP_DEFINE_CONST_FUN_OBJ_1(gateway_mainer_obj, gateway_handle_main);

// bind objects 4 stuff to python names 4 stuff
STATIC const mp_rom_map_elem_t gateway_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_gateway) },
    { MP_ROM_QSTR(MP_QSTR_handle_main), MP_ROM_PTR(&gateway_mainer_obj) },
};


STATIC MP_DEFINE_CONST_DICT(gateway_module_globals, gateway_module_globals_table);

const mp_obj_module_t gateway_user_cmodule = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&gateway_module_globals,
};

MP_REGISTER_MODULE(MP_QSTR_gateway, gateway_user_cmodule, MODULE_GATEWAY_ENABLED);
