#ifndef WRAPPED_H
#define WRAPPED_H
#include <napi.h>

void abortW(Napi::CallbackInfo&);
void configureW(Napi::CallbackInfo&);
void update_nextW(Napi::CallbackInfo&);
void update_currentW(Napi::CallbackInfo&);
void update_holdW(Napi::CallbackInfo&);
void update_incomingW(Napi::CallbackInfo&);
void update_comboW(Napi::CallbackInfo&);
void update_b2bW(Napi::CallbackInfo&);
void update_fieldW(Napi::CallbackInfo&);
void update_resetW(Napi::CallbackInfo&);
void actionW(Napi::CallbackInfo&);
void aliveW(Napi::CallbackInfo&);
void findpathW(Napi::CallbackInfo&);
void actionW(Napi::CallbackInfo&);

#endif