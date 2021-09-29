#include <napi.h>
#include "wrapped.h"
#include "MisaMinoNET\MisaMinoNET\MisaMino\main.h"

using namespace std;

void abortW(const Napi::CallbackInfo& info) {
    Abort();
    return;
}

// Object, Boolean, Boolean, Boolean, Number, Boolean, Boolean
void configureW(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    // 0 Object > AI_Param
    Napi::Object obj0 = info[0].As<Napi::Object>();
    AI::AI_Param arg0 = AI::AI_Param();
    arg0.miny_factor = obj0.Get("miny_factor").As<Napi::Number>();
    arg0.hole = obj0.Get("hole").As<Napi::Number>();
    arg0.open_hole = obj0.Get("open_hole").As<Napi::Number>();
    arg0.v_transitions = obj0.Get("v_transitions").As<Napi::Number>();
    arg0.tspin3 = obj0.Get("tspin3").As<Napi::Number>();
    arg0.clear_efficient = obj0.Get("clear_efficient").As<Napi::Number>();
    arg0.upcomeAtt = obj0.Get("upcomeAtt").As<Napi::Number>();
    arg0.h_factor = obj0.Get("h_factor").As<Napi::Number>();
    arg0.hole_dis_factor2 = obj0.Get("hole_dis_factor2").As<Napi::Number>();
    arg0.hole_dis = obj0.Get("hole_dis").As<Napi::Number>();
    arg0.hole_dis_factor = obj0.Get("hole_dis_factor").As<Napi::Number>();
    arg0.tspin = obj0.Get("tspin").As<Napi::Number>();
    arg0.hold_T = obj0.Get("hold_T").As<Napi::Number>();
    arg0.hold_I = obj0.Get("hold_I").As<Napi::Number>();
    arg0.clear_useless_factor = obj0.Get("clear_useless_factor").As<Napi::Number>();
    arg0.dif_factor = obj0.Get("dif_factor").As<Napi::Number>();
    arg0.b2b = obj0.Get("b2b").As<Napi::Number>();
    arg0.combo = obj0.Get("combo").As<Napi::Number>();
    arg0.avoid_softdrop = obj0.Get("avoid_softdrop").As<Napi::Number>();
    arg0.tmini = obj0.Get("tmini").As<Napi::Number>();

    // 1
    bool arg1 = info[1].As<Napi::Boolean>();

    // 2
    bool arg2 = info[2].As<Napi::Boolean>();

    // 3
    bool arg3 = info[3].As<Napi::Boolean>();

    // 4
    int arg4 = info[4].As<Napi::Number>();

    // 5
    bool arg5 = info[5].As<Napi::Boolean>();

    // 6
    bool arg6 = info[6].As<Napi::Boolean>();

    configure(
        arg0,
        arg1,
        arg2,
        arg3,
        arg4,
        arg5,
        arg6
    );
    return;
};

// Uint8Array
void update_nextW(const Napi::CallbackInfo& info) {

    // 0 Uint8Array > char*
    Napi::Uint8Array arr0 = info[0].As<Napi::Uint8Array>();
    size_t length0 = arr0.ElementLength();
    char* arg0 = reinterpret_cast<char*>(arr0.ArrayBuffer().Data());

    update_next(arg0);
    return;
}

// Uint8Array
void update_currentW(const Napi::CallbackInfo& info) {

    // 0 Uint8Array > char*
    Napi::Uint8Array arr0 = info[0].As<Napi::Uint8Array>();
    size_t length0 = arr0.ElementLength();
    char* arg0 = reinterpret_cast<char*>(arr0.ArrayBuffer().Data());

    update_current(arg0);
    return;
}

// Uint8Array
void update_holdW(const Napi::CallbackInfo& info) {

    // 0 Uint8Array > char*
    Napi::Uint8Array arr0 = info[0].As<Napi::Uint8Array>();
    size_t length0 = arr0.ElementLength();
    char* arg0 = reinterpret_cast<char*>(arr0.ArrayBuffer().Data());

    update_hold(arg0);
    return;
}

// Number
void update_incomingW(const Napi::CallbackInfo& info) {

    // 0
    int arg0 = info[0].As<Napi::Number>();

    update_incoming(arg0);
    return;
}

// Number
void update_comboW(const Napi::CallbackInfo& info) {

    // 0
    int arg0 = info[0].As<Napi::Number>();

    update_combo(arg0);
    return;
}

// Number
void update_b2bW(const Napi::CallbackInfo& info) {

    // 0
    int arg0 = info[0].As<Napi::Number>();

    update_b2b(arg0);
    return;
}

// Number
void update_fieldW(const Napi::CallbackInfo& info) {

    // 0 Uint8Array > char*
    Napi::Uint8Array arr0 = info[0].As<Napi::Uint8Array>();
    size_t length0 = arr0.ElementLength();
    char* arg0 = reinterpret_cast<char*>(arr0.ArrayBuffer().Data());

    update_field(arg0);
    return;
}

void update_resetW(const Napi::CallbackInfo& info) {
    update_reset();
    return;
}

// Uint8Array, Number
void actionW(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    // 0 Uint8Array > char*
    Napi::Uint8Array arr0 = info[0].As<Napi::Uint8Array>();
    size_t length0 = arr0.ElementLength();
    char* arg0 = reinterpret_cast<char*>(arr0.ArrayBuffer().Data());

    // 1
    int arg1 = info[1].As<Napi::Number>();

    action(arg0, arg1);
    return;
}

Napi::Boolean aliveW(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::Boolean returnValue = Napi::Boolean::New(env, alive());
    return returnValue;
}

// Uint8Array, Uint8Array, Number, Number, Number, Boolean, Uint8Array, Number
void findpathW(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    // 0 Uint8array > char*
    Napi::Uint8Array arr0 = info[0].As<Napi::Uint8Array>();
    size_t length0 = arr0.ElementLength();
    char* arg0 = reinterpret_cast<char*>(arr0.ArrayBuffer().Data());

    // 1 Uint8array > char*
    Napi::Uint8Array arr1 = info[1].As<Napi::Uint8Array>();
    size_t length1 = arr1.ElementLength();
    char* arg1 = reinterpret_cast<char*>(arr1.ArrayBuffer().Data());

    // 2
    int arg2 = info[2].As<Napi::Number>();

    // 3
    int arg3 = info[3].As<Napi::Number>();

    // 4
    int arg4 = info[4].As<Napi::Number>();

    // 5
    int arg5 = info[5].As<Napi::Number>();

    // 6 Uint8array > char*
    Napi::Uint8Array arr6 = info[6].As<Napi::Uint8Array>();
    size_t length6 = arr6.ElementLength();
    char* arg6 = reinterpret_cast<char*>(arr6.ArrayBuffer().Data());

    // 5
    int arg7 = info[7].As<Napi::Number>();

    findpath(
        arg0,
        arg1,
        arg2,
        arg3,
        arg4,
        arg5,
        arg6,
        arg7
    );
    return;
}