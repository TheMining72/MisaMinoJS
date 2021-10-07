#include "napi.h"
#include "utils.h"

std::vector<std::vector<std::string>> to_field(Napi::Array arr) {
    int width = arr.Length();
    int height = arr.operator[]((uint32_t) 0).operator Napi::Value().As<Napi::Array>().Length();
    std::vector<std::vector<std::string>> field = std::vector<std::vector<std::string>>();

    for (int x = 0; x < width; ++x) {
        field.push_back(std::vector<std::string>());
        for (int y = 0; y < height; ++y)
            field[x].push_back(arr[x].operator Napi::Value().As<Napi::Array>()[y].operator Napi::Value().As<Napi::String>());
    }

    return field;
}

int clear_lines(std::vector<std::vector<std::string>>* board)
{
    int cleared = 0;

    for (int i = (*board)[0].size() - 1; i >= 0; --i)
    {
        int filled = true;
        for (int j = 0; j < (*board).size() && filled; ++j)
            if ((*board)[j][i] == " ") filled = false;

        if (filled)
        {
            ++cleared;
            for (int j = i; j < (*board)[0].size(); ++j)
            {
                for (int k = 0; k < (*board).size(); ++k)
                {
                    if (j + 1 < (*board)[0].size())
                        (*board)[k][j] = (*board)[k][j + 1];
                    else (*board)[k][j] = " ";
                }
            }
        }
    }

    return cleared;
}

std::vector<std::string> split(std::string s, std::string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find (delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

const std::string to_char[7] = {
    "Z", "S", "L", "J", "T", "O", "I"
};

const std::string piece_defs[7][4][4][4] = {
    { // S
        {
            {" ", "S", "S", " "},
            {"S", "S", " ", " "},
            {" ", " ", " ", " "},
            {" ", " ", " ", " "}
        },
        {
            {" ", "S", " ", " "},
            {" ", "S", "S", " "},
            {" ", " ", "S", " "},
            {" ", " ", " ", " "}
        },
        {
            {" ", " ", " ", " "},
            {" ", "S", "S", " "},
            {"S", "S", " ", " "},
            {" ", " ", " ", " "}
        },
        {
            {"S", " ", " ", " "},
            {"S", "S", " ", " "},
            {" ", "S", " ", " "},
            {" ", " ", " ", " "}
        }
    },
    { // Z
        {
            {"Z", "Z", " ", " "},
            {" ", "Z", "Z", " "},
            {" ", " ", " ", " "},
            {" ", " ", " ", " "}
        },
        {
            {" ", " ", "Z", " "},
            {" ", "Z", "Z", " "},
            {" ", "Z", " ", " "},
            {" ", " ", " ", " "}
        },
        {
            {" ", " ", " ", " "},
            {"Z", "Z", " ", " "},
            {" ", "Z", "Z", " "},
            {" ", " ", " ", " "}
        },
        {
            {" ", "Z", " ", " "},
            {"Z", "Z", " ", " "},
            {"Z", " ", " ", " "},
            {" ", " ", " ", " "}
        }
    },
    { // J
        {
            {"J", " ", " ", " "},
            {"J", "J", "J", " "},
            {" ", " ", " ", " "},
            {" ", " ", " ", " "}
        },
        {
            {" ", "J", "J", " "},
            {" ", "J", " ", " "},
            {" ", "J", " ", " "},
            {" ", " ", " ", " "}
        },
        {
            {" ", " ", " ", " "},
            {"J", "J", "J", " "},
            {" ", " ", "J", " "},
            {" ", " ", " ", " "}
        },
        {
            {" ", "J", " ", " "},
            {" ", "J", " ", " "},
            {"J", "J", " ", " "},
            {" ", " ", " ", " "}
        }
    },
    { // L
        {
            {" ", " ", "L", " "},
            {"L", "L", "L", " "},
            {" ", " ", " ", " "},
            {" ", " ", " ", " "}
        },
        {
            {" ", "L", " ", " "},
            {" ", "L", " ", " "},
            {" ", "L", "L", " "},
            {" ", " ", " ", " "}
        },
        {
            {" ", " ", " ", " "},
            {"L", "L", "L", " "},
            {"L", " ", " ", " "},
            {" ", " ", " ", " "}
        },
        {
            {"L", "L", " ", " "},
            {" ", "L", " ", " "},
            {" ", "L", " ", " "},
            {" ", " ", " ", " "}
        }
    },
    { // T
        {
            {" ", "T", " ", " "},
            {"T", "T", "T", " "},
            {" ", " ", " ", " "},
            {" ", " ", " ", " "}
        },
        {
            {" ", "T", " ", " "},
            {" ", "T", "T", " "},
            {" ", "T", " ", " "},
            {" ", " ", " ", " "}
        },
        {
            {" ", " ", " ", " "},
            {"T", "T", "T", " "},
            {" ", "T", " ", " "},
            {" ", " ", " ", " "}
        },
        {
            {" ", "T", " ", " "},
            {"T", "T", " ", " "},
            {" ", "T", " ", " "},
            {" ", " ", " ", " "}
        }
    },
    { // O
        {
            {" ", "O", "O", " "},
            {" ", "O", "O", " "},
            {" ", " ", " ", " "},
            {" ", " ", " ", " "}
        },
        {
            {" ", "O", "O", " "},
            {" ", "O", "O", " "},
            {" ", " ", " ", " "},
            {" ", " ", " ", " "}
        },
        {
            {" ", "O", "O", " "},
            {" ", "O", "O", " "},
            {" ", " ", " ", " "},
            {" ", " ", " ", " "}
        },
        {
            {" ", "O", "O", " "},
            {" ", "O", "O", " "},
            {" ", " ", " ", " "},
            {" ", " ", " ", " "}
        }
    },
    { // I
        {
            {" ", " ", " ", " "},
            {"I", "I", "I", "I"},
            {" ", " ", " ", " "},
            {" ", " ", " ", " "}
        },
        {
            {" ", " ", "I", " "},
            {" ", " ", "I", " "},
            {" ", " ", "I", " "},
            {" ", " ", "I", " "}
        },
        {
            {" ", " ", " ", " "},
            {" ", " ", " ", " "},
            {"I", "I", "I", "I"},
            {" ", " ", " ", " "}
        },
        {
            {" ", "I", " ", " "},
            {" ", "I", " ", " "},
            {" ", "I", " ", " "},
            {" ", "I", " ", " "}
        }
    }
};