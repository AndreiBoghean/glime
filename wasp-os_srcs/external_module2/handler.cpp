// Include the header file to get access to the MicroPython API
#include "py/dynruntime.h"
#include "externApp.h"
#include "compat.h"

// This is the function which will be called from Python, as factorial(x)
static mp_obj_t handler(mp_obj_t callback) {
    // mp_int_t result = null_function();
	init(&callback);
	extern_main();	
	
	// return 0;
    return mp_obj_new_int(0); // Convert the result to a MicroPython integer object and return it
}

// Define a Python reference to the function above
static MP_DEFINE_CONST_FUN_OBJ_1(handler_obj, handler);

// This is the entry point and is called when the module is imported
extern "C" mp_obj_t mpy_init(mp_obj_fun_bc_t *self, size_t n_args, size_t n_kw, mp_obj_t *args) {
    // This must be first, it sets up the globals dict and other things
    MP_DYNRUNTIME_INIT_ENTRY

    // Make the function available in the module's namespace
    mp_store_global(MP_QSTR_extern_main_handler, MP_OBJ_FROM_PTR(&handler_obj));

    // This must be last, it restores the globals dict
    MP_DYNRUNTIME_INIT_EXIT
}
