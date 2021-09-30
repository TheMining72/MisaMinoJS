#ifndef WRAPPED_H
#define WRAPPED_H
#include <napi.h>

napi_value configureW(const Napi::CallbackInfo& info);
napi_value update_nextW(const Napi::CallbackInfo& info);
napi_value update_currentW(const Napi::CallbackInfo& info);
napi_value update_holdW(const Napi::CallbackInfo& info);
napi_value update_incomingW(const Napi::CallbackInfo& info);
napi_value update_comboW(const Napi::CallbackInfo& info);
napi_value update_b2bW(const Napi::CallbackInfo& info);
napi_value update_fieldW(const Napi::CallbackInfo& info);
napi_value update_resetW(const Napi::CallbackInfo& info);
napi_value actionW(const Napi::CallbackInfo& info);
Napi::Boolean aliveW(const Napi::CallbackInfo& info);
napi_value findpathW(const Napi::CallbackInfo& info);

#endif