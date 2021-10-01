#include <napi.h>
#include "wrapped.h"

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set("finished_add", Napi::Function::New(env, finished_add));
    exports.Set("finished_del", Napi::Function::New(env, finished_del));
    // exports.Set("abort", Napi::Function::New(env, abortW));
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
    //exports.Set("findpath", Napi::Function::New(env, findpathW));
    return exports;
}

NODE_API_MODULE(MisaMinoJS, Init)