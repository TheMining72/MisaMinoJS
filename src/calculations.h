#ifndef CALCULATIONS_H
#define CALCULATIONS_H
#include <napi.h>
#include "wrapped.h"

Napi::Value start(const Napi::CallbackInfo& info);
napi_value move(const Napi::CallbackInfo& info);

#endif