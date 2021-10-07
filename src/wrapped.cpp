#include <napi.h>
#include "wrapped.h"
#include "calculations.h"
#include "utils.h"
#include "./MisaMino/MisaMino/main.h"

extern "C" void configure(AI::AI_Param param, bool holdAllowed, bool allSpin, bool TSDonly, int search_width, bool allow180, bool srsplus);
extern "C" void update_next(const char* queue);
extern "C" void update_current(const char* piece);
extern "C" void update_hold(const char* piece);
extern "C" void update_incoming(int attack);
extern "C" void update_combo(int combo);
extern "C" void update_b2b(int b2b);
extern "C" void update_field(const char* field);
extern "C" void update_reset();
extern "C" bool alive();
extern "C" void findpath(const char* _field, const char* _piece, int x, int y, int r, bool hold, char* str, int len);

bool aborting = false;
bool mm_running = false;
bool running = false;

int abort_callback() {
    return aborting;
}

napi_value abort_bot(const Napi::CallbackInfo& info) {
    if (mm_running) aborting = true;
    return nullptr;
}

// Object, Boolean, Boolean, Boolean, Number, Boolean, Boolean
napi_value configureW(const Napi::CallbackInfo& info) {
    // 0 Object > AI_Param
    Napi::Object obj0 = info.Length() > 0 ? info[0].As<Napi::Object>() : Napi::Object::New(info.Env());
    AI::AI_Param arg0 = AI::AI_Param();
    arg0.miny_factor = obj0.Has("miny_factor") ? obj0.Get("miny_factor").As<Napi::Number>() : 16;
    arg0.hole = obj0.Has("hole") ? obj0.Get("hole").As<Napi::Number>() : 9;
    arg0.open_hole = obj0.Has("open_hole") ? obj0.Get("open_hole").As<Napi::Number>() : 11;
    arg0.v_transitions = obj0.Has("v_transitions") ? obj0.Get("v_transitions").As<Napi::Number>() : 17;
    arg0.tspin3 = obj0.Has("tspin3") ? obj0.Get("tspin3").As<Napi::Number>() : 17;
    arg0.clear_efficient = obj0.Has("clear_efficient") ? obj0.Get("clear_efficient").As<Napi::Number>() : 25;
    arg0.upcomeAtt = obj0.Has("upcomeAtt") ? obj0.Get("upcomeAtt").As<Napi::Number>() : 39;
    arg0.h_factor = obj0.Has("h_factor") ? obj0.Get("h_factor").As<Napi::Number>() : 2;
    arg0.hole_dis_factor2 = obj0.Has("hole_dis_factor2") ? obj0.Get("hole_dis_factor2").As<Napi::Number>() : 12;
    arg0.hole_dis = obj0.Has("hole_dis") ? obj0.Get("hole_dis").As<Napi::Number>() : 19;
    arg0.hole_dis_factor = obj0.Has("hole_dis_factor") ? obj0.Get("hole_dis_factor").As<Napi::Number>() : 7;
    arg0.tspin = obj0.Has("tspin") ? obj0.Get("tspin").As<Napi::Number>() : 24;
    arg0.hold_T = obj0.Has("hold_T") ? obj0.Get("hold_T").As<Napi::Number>() : 18;
    arg0.hold_I = obj0.Has("hold_I") ? obj0.Get("hold_I").As<Napi::Number>() : 7;
    arg0.clear_useless_factor = obj0.Has("clear_useless_factor") ? obj0.Get("clear_useless_factor").As<Napi::Number>() : 14;
    arg0.dif_factor = obj0.Has("dif_factor") ? obj0.Get("dif_factor").As<Napi::Number>() : 19;
    arg0.b2b = obj0.Has("b2b") ? obj0.Get("b2b").As<Napi::Number>() : 99;
    arg0.combo = obj0.Has("combo") ? obj0.Get("combo").As<Napi::Number>() : 14;
    arg0.avoid_softdrop = obj0.Has("avoid_softdrop") ? obj0.Get("avoid_softdrop").As<Napi::Number>() : 19;
    arg0.tmini = obj0.Has("tmini") ? obj0.Get("tmini").As<Napi::Number>() : 0;
    arg0.tmini = obj0.Has("strategy_4w") ? obj0.Get("strategy_4w").As<Napi::Number>() : 0;

    // 1
    bool arg1 = info.Length() > 1 ? info[1].As<Napi::Boolean>() : true;

    // 2
    bool arg2 = info.Length() > 2 ? info[2].As<Napi::Boolean>() : false;

    // 3
    bool arg3 = info.Length() > 3 ? info[3].As<Napi::Boolean>() : false;

    // 4
    int arg4 = info.Length() > 4 ? info[4].As<Napi::Number>() : 1000;

    // 5
    bool arg5 = info.Length() > 5 ? info[5].As<Napi::Boolean>() : true;

    // 6
    bool arg6 = info.Length() > 6 ? info[6].As<Napi::Boolean>() : true;

    configure(
    arg0,
    arg1,
    arg2,
    arg3,
    arg4,
    arg5,
    arg6
    );
    return nullptr;
};

// String[]
napi_value update_nextW(const Napi::CallbackInfo& info) {
    // 0 Number[] > char*
    Napi::Array arr0 = info[0].As<Napi::Array>();
    std::string arg0 = "";
    arg0 += arr0.operator[]((uint32_t) 0).operator Napi::Value().As<Napi::String>();
    for (int i = 1; i < arr0.Length(); ++i)
    arg0 += "," + (std::string) arr0.operator[]((uint32_t) i).operator Napi::Value().As<Napi::String>();
    for (int i = 0; i < arg0.size(); ++i) arg0[i] = toupper(arg0[i]);

    update_next(arg0.c_str());
    return nullptr;
}

// String
napi_value update_currentW(const Napi::CallbackInfo& info) {
    // 0 String > char*
    std::string arg0 = info[0].As<Napi::String>();
    for (int i = 0; i < arg0.size(); ++i) arg0[i] = toupper(arg0[i]);
    update_current(arg0.c_str());
    return nullptr;
}

// Number
napi_value update_holdW(const Napi::CallbackInfo& info) {
    // 0 Number > char*, just directly put it in because
    if (info.Length() > 0) {
        if (!info[0].IsNull()) {
            std::string arg0 = info[0].As<Napi::String>();
            for (int i = 0; i < arg0.size(); ++i) arg0[i] = toupper(arg0[i]);
            update_hold(arg0.c_str());
        }
        else update_hold(" ");
    }
    else update_hold(" ");
    return nullptr;
}

// Number
napi_value update_incomingW(const Napi::CallbackInfo& info) {
    // 0
    int arg0 = info[0].As<Napi::Number>();

    update_incoming(arg0);
    return nullptr;
}

// Number
napi_value update_comboW(const Napi::CallbackInfo& info) {
    // 0
    int arg0 = info[0].As<Napi::Number>();

    update_combo(arg0);
    return nullptr;
}

// Number
napi_value update_b2bW(const Napi::CallbackInfo& info) {
    // 0
    int arg0 = info[0].As<Napi::Number>();

    update_b2b(arg0);
    return nullptr;
}

// Number[][]
napi_value update_fieldW(const Napi::CallbackInfo& info) {
    // Number[][] > char*
    std::vector<std::vector<std::string>> field = to_field(info[0].As<Napi::Array>());
    int width = field.size();
    int height = field[0].size();

    std::vector<std::string> rows = std::vector<std::string>();
    for (int i = 0; i < height; ++i) rows.push_back("");

    for (int i = 0; i < height; ++i) {
        std::vector<int> row = std::vector<int>();
        for (int i = 0; i < width; ++i) row.push_back(0);

        for (int j = 0; j < width; ++j)
            row[width - 1 - j] = (field[j][i] == " ") ? 0 : 2; // Mirror for whatever reason. Blaming MisaMino.

        std::string row_str = ""; 
        row_str += std::to_string(row[0]); 
        for (int i = 1; i < width; ++i)
        row_str += "," + std::to_string(row[i]);

        rows[height - i - 1] = row_str;
    }

    std::string rows_str = ""; 
    rows_str += rows[0]; 
    for (int i = 1; i < height; ++i)
    rows_str += ";" + rows[i];

    update_field(rows_str.c_str());
    return nullptr;
}

napi_value update_resetW(const Napi::CallbackInfo& info) {
    update_reset();
    return nullptr;
}

Napi::Boolean is_running(const Napi::CallbackInfo& info) {
    return Napi::Boolean::New(info.Env(), running);
}

Napi::Value actionW(const Napi::CallbackInfo& info) {
    if (running) napi_throw_error(info.Env(), 0, "Cannot start another action while one is already running");
    aborting = false;
    running = true;
    auto a = Napi::Function::New(info.Env(), start);
    return a.Call(std::vector<napi_value>());
}

Napi::Boolean aliveW(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::Boolean returnValue = Napi::Boolean::New(env, alive());
    return returnValue;
}

napi_value findpathW(const Napi::CallbackInfo& info) {
    return nullptr;
}

// Array, Object
// Array, String, Number, Number, Number
Napi::Object apply_piece(const Napi::CallbackInfo& info) {
    bool success = true;
    
    std::vector<std::vector<std::string>> board;
    int piece;
    int x;
    int y;
    int r;

    board = to_field(info[0].As<Napi::Array>());

    if (info[0].IsObject()) {
        Napi::Object solution = info[1].ToObject();

        const std::string* piece_str = std::find(std::begin(to_char), std::end(to_char), ((std::string) solution["PieceUsed"].operator Napi::Value().ToString()));
        if (piece_str != std::end(to_char)) piece = std::distance(to_char, piece_str);
        else {
            napi_throw_error(info.Env(), nullptr, "Given piece string was not 'S', 'Z', 'J', 'L', 'T', 'O' or 'I'");
            return Napi::Array::New(info.Env());
        }

        x = solution["FinalX"].operator Napi::Value().ToNumber();
        y = solution["FinalY"].operator Napi::Value().ToNumber();
        r = solution["FinalR"].operator Napi::Value().ToNumber();
    }
    else {
        const std::string* piece_str = std::find(std::begin(to_char), std::end(to_char), ((std::string) info[1].ToString()));
        if (piece_str != std::end(to_char)) piece = std::distance(to_char, piece_str);
        else {
            napi_throw_error(info.Env(), nullptr, "Given piece string was not 'S', 'Z', 'J', 'L', 'T', 'O' or 'I'");
            return Napi::Array::New(info.Env());
        }

        x = info[2].ToNumber();
        y = info[3].ToNumber();
        r = info[4].ToNumber();
    }

    int base_board_height = board[0].size();

    bool cleared_lines = false;
    --x;
    y = base_board_height + 3 - y;

    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            if (piece_defs[piece][r][i][j] != " ")
            {
                if (x + j < 0 || y - i < 0 || x + j > board.size() || y - i > board[0].size() || board[x + j][y - i] != " ") success = false;
                board[x + j][y - i] = piece_defs[piece][r][i][j];
            }

    Napi::Array new_field;
    cleared_lines = clear_lines(&board) > 0;
    new_field = Napi::Array::New(info.Env());
    for (int x = 0; x < board.size(); ++x) {
        new_field[x] = Napi::Array::New(info.Env());
        for (int y = 0; y < board[x].size(); ++y)
            new_field.operator[]((uint32_t) x).operator Napi::Value().As<Napi::Array>().operator[]((uint32_t) y).operator=(Napi::String::New(info.Env(), board[x][y]));
    }

    Napi::Object field_info = Napi::Object::New(info.Env());
    field_info["Success"] = Napi::Boolean::New(info.Env(), success);
    field_info["Field"] = new_field;
    field_info["Combo"] = Napi::Boolean::New(info.Env(), cleared_lines);

    return field_info;
}

// Array, Array
Napi::Array add_garbage(const Napi::CallbackInfo& info) {
    std::vector<std::vector<std::string>> board = to_field(info[0].As<Napi::Array>());;

    std::vector<int> holes = std::vector<int>();
    auto holes_jsarr = info[1].As<Napi::Array>();
    for (int i = 0; i < holes_jsarr.Length(); ++i)
        holes.push_back(holes_jsarr[i].operator Napi::Value().ToNumber());

    while (holes.size() > board[0].size()) {
        holes.erase(holes.cbegin());
    }

    for (int y = holes.size() - 1; y >= 0; --y) {
        for (int x = 0; x < board.size(); ++x)
            board[x][y] = (-(x - board.size() + 1) == holes[-(y - holes.size() + 1)]) ? " " : "G";
    }

    Napi::Array new_field = Napi::Array::New(info.Env());
    for (int x = 0; x < board.size(); ++x) {
        new_field[x] = Napi::Array::New(info.Env());
        for (int y = 0; y < board[x].size(); ++y)
            new_field.operator[]((uint32_t) x).operator Napi::Value().As<Napi::Array>().operator[]((uint32_t) y).operator=(Napi::String::New(info.Env(), board[x][y]));
    }

    return new_field;
}