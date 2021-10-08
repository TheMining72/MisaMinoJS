#ifndef WRAPPED_H
#define WRAPPED_H
#include <napi.h>
#include "utils.h"

extern bool aborting;
extern bool running;

int abort_callback();

napi_value configureW(const Napi::CallbackInfo& info);
napi_value update_nextW(const Napi::CallbackInfo& info);
napi_value update_currentW(const Napi::CallbackInfo& info);
napi_value update_holdW(const Napi::CallbackInfo& info);
napi_value update_incomingW(const Napi::CallbackInfo& info);
napi_value update_comboW(const Napi::CallbackInfo& info);
napi_value update_b2bW(const Napi::CallbackInfo& info);
napi_value update_fieldW(const Napi::CallbackInfo& info);
napi_value update_resetW(const Napi::CallbackInfo& info);
Napi::Value actionW(const Napi::CallbackInfo& info);
Napi::Boolean aliveW(const Napi::CallbackInfo& info);

napi_value abort_bot(const Napi::CallbackInfo& info);
Napi::Boolean is_running(const Napi::CallbackInfo& info);
Napi::Object apply_piece(const Napi::CallbackInfo& info);
Napi::Array add_garbage(const Napi::CallbackInfo& info);

#endif