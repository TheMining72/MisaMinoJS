#include <napi.h>
#include "wrapped.h"
#include "calculations.h"
#include "./MisaMino/MisaMino/main.h"

std::string move() {
    if (aborting) return "-1";
    aborting = false;
    mm_running = true;
    std::string solution = action();
    mm_running = false;
    return solution;
}

struct move_context {
    const static void start(move_context* context) {
        context -> solution = move();
        context -> tsfn.Release();
        running = false;
    }

    move_context(Napi::Env env) : deferred(Napi::Promise::Deferred::New(env)) { };

    // Native Promise returned to JavaScript
    Napi::Promise::Deferred deferred;

    // Native thread
    std::thread nativeThread;

    Napi::ThreadSafeFunction tsfn;

    std::string solution;
};

napi_value finished(const Napi::CallbackInfo& info) {
    std::vector<napi_value> args = std::vector<napi_value>();
    args.push_back(info[0]);
    for (Napi::Function f : finished_hook) 
        f.Call(args);
    return nullptr;
}

void FinalizerCallback(Napi::Env env, void *finalizeData, move_context *context) {
    // Join the thread
    context -> nativeThread.join();

    // Resolve the Promise previously returned to JS
    context -> deferred.Resolve(Napi::String::New(env, context -> solution));
    delete context;
}

Napi::Value start(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    auto move_data = new move_context(env);

    move_data -> tsfn = Napi::ThreadSafeFunction::New(
        info.Env(),
        Napi::Function::New(info.Env(), finished),
        Napi::Object::New(info.Env()),
        "Action",
        0,
        1,
        move_data,
        FinalizerCallback,
        (void*) nullptr
    );

    move_data -> nativeThread = std::thread(move_data -> start, move_data);

    return move_data -> deferred.Promise();
}