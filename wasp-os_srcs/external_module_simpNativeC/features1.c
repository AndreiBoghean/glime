// Include the header file to get access to the MicroPython API
#include "py/dynruntime.h"

STATIC mp_obj_t get_num() {
    return mp_obj_new_int(42);
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(getnum_obj, get_num);

// This is the entry point and is called when the module is imported
mp_obj_t mpy_init(mp_obj_fun_bc_t *self, size_t n_args, size_t n_kw, mp_obj_t *args) {
    // This must be first, it sets up the globals dict and other things
    MP_DYNRUNTIME_INIT_ENTRY

    // Make the functions available in the module's namespace
    mp_store_global(MP_QSTR_get_num, MP_OBJ_FROM_PTR(&getnum_obj));

    // This must be last, it restores the globals dict
    MP_DYNRUNTIME_INIT_EXIT
}
