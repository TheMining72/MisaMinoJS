#include <napi.h>
#include "wrapped.h"
#include "./MisaMino/MisaMino/main.h"

bool first_setup = true;
extern "C" void setup();
extern "C" void set_abort(Callback handler);

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    if (first_setup) {
        setup();
        set_abort(abort_callback);
        first_setup = false;
    }

    exports.Set("configure", Napi::Function::New(env, configureW));
    exports.Set("update_next", Napi::Function::New(env, update_nextW));
    exports.Set("update_current", Napi::Function::New(env, update_currentW));
    exports.Set("update_hold", Napi::Function::New(env, update_holdW));
    exports.Set("update_incoming", Napi::Function::New(env, update_incomingW));
    exports.Set("update_combo", Napi::Function::New(env, update_comboW));
    exports.Set("update_b2b", Napi::Function::New(env, update_b2bW));
    exports.Set("update_field", Napi::Function::New(env, update_fieldW));
    exports.Set("update_reset", Napi::Function::New(env, update_resetW));
    exports.Set("action", Napi::Function::New(env, actionW));
    exports.Set("alive", Napi::Function::New(env, aliveW));

    exports.Set("abort", Napi::Function::New(env, abort_bot));
    exports.Set("is_running", Napi::Function::New(env, is_running));
    exports.Set("apply_piece", Napi::Function::New(env, apply_piece));
    exports.Set("add_garbage", Napi::Function::New(env, add_garbage));
    return exports;
}

NODE_API_MODULE(MisaMinoJS, Init)