#include <napi.h>
#include "wrapped.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
 //   set_abort(abort);
    
    Napi::Object raw = Napi::Object::New(env);
    //raw.Set("abort", Napi::Function::New(env, abortW));
    raw.Set("configure", Napi::Function::New(env, configureW));
    raw.Set("update_next", Napi::Function::New(env, update_nextW));
    raw.Set("update_current", Napi::Function::New(env, update_currentW));
    raw.Set("update_hold", Napi::Function::New(env, update_holdW));
    raw.Set("update_incoming", Napi::Function::New(env, update_incomingW));
    raw.Set("update_combo", Napi::Function::New(env, update_comboW));
    raw.Set("update_b2b", Napi::Function::New(env, update_b2bW));
    raw.Set("update_field", Napi::Function::New(env, update_fieldW));
    raw.Set("update_reset", Napi::Function::New(env, update_resetW));
    raw.Set("action", Napi::Function::New(env, actionW));
    raw.Set("alive", Napi::Function::New(env, aliveW));
    raw.Set("findpath", Napi::Function::New(env, findpathW));

    exports.Set("_raw", raw);

	return exports;
}

NODE_API_MODULE(MisaMinoJS, InitAll)