#include <napi.h>
#include "wrapped.h"
#include "calculations.h"
#include "./MisaMino/MisaMino/main.h"

struct move_context {
    #ifndef _WIN32
    static void* posix_move(void* context) {
        ((move_context*) context) -> move((move_context*) context);
        return nullptr;
    }
    #endif

    const static void move(move_context* context) {
        running = true;
        context -> solution = action();
        running = false;
        context -> tsfn.Release();
    }

    move_context(Napi::Env env) : deferred(Napi::Promise::Deferred::New(env)) { };

    Napi::Promise::Deferred deferred;
    #ifdef _WIN32
    std::thread nativeThread;
    #else
    pthread_t* nativeThread;
    #endif
    Napi::ThreadSafeFunction tsfn;
    std::string solution;
};

void FinalizerCallback(Napi::Env env, void *finalizeData, move_context *context) {
    #ifdef _WIN32
    context -> nativeThread.join();
    #endif

    if (context -> solution == "-1") {
        context -> deferred.Resolve(Napi::Number::New(env, -1));
        return;
    }

    std::vector<std::string> info = split(context -> solution, "|");

    Napi::Array instructions = Napi::Array::New(env);
    std::vector<std::string> instructionInfo = split(info[0], ",");
    for (int i = 0; i < instructionInfo.size(); ++i)
        instructions[i] = Napi::Number::New(env, std::stoi(instructionInfo[i]));

    Napi::String pieceUsed = Napi::String::New(env, info[1]);
    Napi::Boolean spinUsed = Napi::Boolean::New(env, std::stoi(info[2]));
    Napi::Number b2b = Napi::Number::New(env, std::stoi(info[3]));
    Napi::Number nodes = Napi::Number::New(env, std::stoi(info[4]));
    Napi::Number depth = Napi::Number::New(env, std::stoi(info[5]));
    Napi::Number attack = Napi::Number::New(env, std::stoi(info[6]));

    std::vector<std::string> pieceInfo = split(info[7], ",");
    Napi::Number finalX = Napi::Number::New(env, std::stoi(pieceInfo[0]) + 1);
    Napi::Number finalY = Napi::Number::New(env, std::stoi(pieceInfo[1]) + 3);

    Napi::Object solution = Napi::Object::New(env);
    solution["Instructions"] = instructions;
    solution["PieceUsed"] = pieceUsed;
    solution["SpinUsed"] = spinUsed;
    solution["B2B"] = b2b;
    solution["Nodes"] = nodes;
    solution["Depth"] = depth;
    solution["Attack"] = attack;
    solution["FinalX"] = finalX;
    solution["FinalY"] = finalY;

    context -> deferred.Resolve(solution);
    delete context;
}

Napi::Promise start(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    auto move_data = new move_context(env);

    move_data -> tsfn = Napi::ThreadSafeFunction::New(
        info.Env(),
        Napi::Function(),
        Napi::Object::New(info.Env()),
        "Action",
        0,
        1,
        move_data,
        FinalizerCallback,
        (void*) nullptr
    );

    aborting = false;
    #ifdef _WIN32
    move_data -> nativeThread = std::thread(move_data -> move, move_data);
    #else
    pthread_t action_thread;
    move_data -> nativeThread = &action_thread;
    if(pthread_create(&action_thread, nullptr, move_data -> posix_move, (void*) move_data) != 0)
        napi_throw_error(info.Env(), 0, "pthread creation failed");
    #endif

    return move_data -> deferred.Promise();
}