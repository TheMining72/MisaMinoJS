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
    //std::vector<napi_value> args = std::vector<napi_value>();
    //args.push_back(info[0]);
    //for (Napi::Function f : finished_hook) 
    //    f.Call(args);
    return nullptr;
}

void FinalizerCallback(Napi::Env env, void *finalizeData, move_context *context) {
    // Join the thread
    context -> nativeThread.join();

    // Resolve the Promise previously returned to JS
    const int* from_misamino = new int[7] { 6, 4, 2, 3, 0, 1, 5 };
    std::vector<std::string> info = split(context -> solution, "|");

    Napi::Array instructions = Napi::Array::New(env);
    std::vector<std::string> instructionInfo = split(info[0], ",");
    for (int i = 0; i < instructionInfo.size(); ++i)
        instructions[i] = Napi::Number::New(env, std::stoi(instructionInfo[i]));

    Napi::String pieceUsed = Napi::String::New(env, info[1]);
    Napi::Number spinUsed = Napi::Number::New(env, std::stoi(info[2]));
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
    delete from_misamino;
    delete context;
}

Napi::Promise start(const Napi::CallbackInfo& info) {
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