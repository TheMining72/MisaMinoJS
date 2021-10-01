#include <napi.h>
#include "./MisaMinoNET/MisaMinoNET/MisaMino/main.h"

extern "C" void set_abort(Callback handler);
extern "C" void configure(AI::AI_Param param, bool holdAllowed, bool allSpin, bool TSDonly, int search_width, bool allow180, bool srsplus);
extern "C" void update_next(const char* queue);
extern "C" void update_current(const char* piece);
extern "C" void update_hold(const char* piece);
extern "C" void update_incoming(int attack);
extern "C" void update_combo(int combo);
extern "C" void update_b2b(int b2b);
extern "C" void update_field(const char* field);
extern "C" void update_reset();
extern "C" void action(char* str, int len);
extern "C" bool alive();
extern "C" void findpath(const char* _field, const char* _piece, int x, int y, int r, bool hold, char* str, int len);

//Callback abort = 0;
std::vector<Napi::Function> finishedHook = std::vector<Napi::Function>();
bool running = false;

napi_value finished_add(const Napi::CallbackInfo& info) {
	finishedHook.push_back(info[6].As<Napi::Function>());
	return nullptr;
}

napi_value finished_del(const Napi::CallbackInfo& info) {
	finishedHook.erase(std::find(finishedHook.begin(), finishedHook.end(), info[6].As<Napi::Function>()));
	return nullptr;
}

//void abortW(const Napi::CallbackInfo& info) {
//    abort();
//    return nullptr;
//}

// Object, Boolean, Boolean, Boolean, Number, Boolean, Boolean
napi_value configureW(const Napi::CallbackInfo& info) {
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
	return nullptr;
};

// Number[]
napi_value update_nextW(const Napi::CallbackInfo& info) {

	// 0 Number[] > char*
	Napi::Array arr0 = info[0].As<Napi::Array>();
    std::string arg0 = "";
    arg0 += std::to_string((int) arr0.operator[]((uint32_t) 0).operator Napi::Value().As<Napi::Number>());
    for (int i = 1; i < arr0.Length(); i++)
        arg0 += "," + std::to_string((int) arr0.operator[]((uint32_t) i).operator Napi::Value().As<Napi::Number>());

	update_next(arg0.c_str());
	return nullptr;
}

// Number
napi_value update_currentW(const Napi::CallbackInfo& info) {

	// 0 Number > char*
	int num0 = info[0].As<Napi::Number>();
	std::string s = std::to_string(num0);
	char const *arg0 = s.c_str();

	update_current(arg0);
	return nullptr;
}

// Number
napi_value update_holdW(const Napi::CallbackInfo& info) {

	// 0 Number > char*
	int num0 = info[0].As<Napi::Number>();
	std::string s = std::to_string(num0);
	char const *arg0 = s.c_str();

	update_hold(arg0);
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

    // Make `field` and `height`
	Napi::Array arr = info[0].As<Napi::Array>();
    int height = arr.Length();

    int** field = new int*[height];
    for (int i = 0; i < height; ++i)
        field[i] = new int[10];

    for (int x = 0; x < 10; x++)
        for (int y = 0; y < height; y++)
            field[x][y] = arr.operator[]((uint32_t) x).operator Napi::Value().As<Napi::Array>().operator[]((uint32_t) y).operator Napi::Value().As<Napi::Number>();

    // Turn the field into a string and give to MisaMino
    std::string* rows = new std::string[height];

    for (int i = 0; i < height; i++) {
        int row[10];

        for (int j = 0; j < 10; j++)
            row[9 - j] = (*field[j, i] == 255) ? 0 : 2; // Mirror for whatever reason. Blaming MisaMino.

        std::string row_str = ""; 
        row_str += std::to_string(row[0]); 
        for (int i = 1; i < 10; i++)
            row_str += "," + std::to_string(row[i]);

        rows[height - i - 1] = row_str;
    }

    std::string rows_str = ""; 
    rows_str += rows[0]; 
    for (int i = 1; i < 10; i++)
        rows_str += ";" + rows[i];

    delete rows;
    for (int i = 0; i < 10; i++) delete field[i];
    delete field;

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

void move(Napi::Env env) {
	char* solution = "";
	action(solution, 0);
	napi_value return_value;
	napi_value arg;
	napi_value global;

	if (napi_get_global(env, &global) != napi_ok) return;
	if (napi_create_string_utf8(env, solution, NAPI_AUTO_LENGTH, &arg) != napi_ok) return;

	napi_value* argv = &arg;
    running = false;
	for (Napi::Function f : finishedHook) 
		napi_call_function(env, global, f, 1, argv, &return_value);
	return;
}

napi_value actionW(const Napi::CallbackInfo& info) {
    running = true;
	std::thread(move, info.Env());
	return nullptr;
}

Napi::Boolean aliveW(const Napi::CallbackInfo& info) {
	Napi::Env env = info.Env();
	Napi::Boolean returnValue = Napi::Boolean::New(env, alive());
	return returnValue;
}

// Uint8Array, Uint8Array, Number, Number, Number, Boolean, Uint8Array, Number
/*napi_value findpathW(const Napi::CallbackInfo& info) {
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
	return nullptr;
}*/