#include "napi.h"
#include "utils.h"

std::vector<std::vector<int>> to_field(Napi::Array arr) {
    int width = arr.Length();
    int height = arr.operator[]((uint32_t) 0).operator Napi::Value().As<Napi::Array>().Length();
    std::vector<std::vector<int>> field = std::vector<std::vector<int>>();

    for (int x = 0; x < width; ++x) {
        field.push_back(std::vector<int>());
        for (int y = 0; y < height; ++y)
            field[x].push_back(arr[x].operator Napi::Value().As<Napi::Array>()[y].operator Napi::Value().As<Napi::Number>());
    }

    return field;
}

std::tuple<std::vector<std::vector<int>>, int> clear_lines(std::vector<std::vector<int>> board)
{
    int cleared = 0;

    for (int i = board[0].size() - 1; i >= 0; --i)
    {
        int fill = 0;
        for (int j = 0; j < board.size(); ++j)
            fill += board[j][i] != -1;

        if (fill >= board.size())
        {
            ++cleared;
            for (int j = i; j < board[0].size(); ++j)
            {
                for (int k = 0; k < board.size(); ++k)
                {
                    if (j + 1 < board[0].size())
                        board[k][j] = board[k][j + 1];
                    else board[k][j] = -1;
                }
            }
        }
    }

    return std::make_tuple(board, cleared);
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

const int piece_defs[7][4][4][4] = {
    { // S
        {
            {-1, 0, 0, -1},
            {0, 0, -1, -1},
            {-1, -1, -1, -1},
            {-1, -1, -1, -1}
        },
        {
            {-1, 0, -1, -1},
            {-1, 0, 0, -1},
            {-1, -1, 0, -1},
            {-1, -1, -1, -1}
        },
        {
            {-1, -1, -1, -1},
            {-1, 0, 0, -1},
            {0, 0, -1, -1},
            {-1, -1, -1, -1}
        },
        {
            {0, -1, -1, -1},
            {0, 0, -1, -1},
            {-1, 0, -1, -1},
            {-1, -1, -1, -1}
        }
    },
    { // Z
        {
            {1, 1, -1, -1},
            {-1, 1, 1, -1},
            {-1, -1, -1, -1},
            {-1, -1, -1, -1}
        },
        {
            {-1, -1, 1, -1},
            {-1, 1, 1, -1},
            {-1, 1, -1, -1},
            {-1, -1, -1, -1}
        },
        {
            {-1, -1, -1, -1},
            {1, 1, -1, -1},
            {-1, 1, 1, -1},
            {-1, -1, -1, -1}
        },
        {
            {-1, 1, -1, -1},
            {1, 1, -1, -1},
            {1, -1, -1, -1},
            {-1, -1, -1, -1}
        }
    },
    { // J
        {
            {2, -1, -1, -1},
            {2, 2, 2, -1},
            {-1, -1, -1, -1},
            {-1, -1, -1, -1}
        },
        {
            {-1, 2, 2, -1},
            {-1, 2, -1, -1},
            {-1, 2, -1, -1},
            {-1, -1, -1, -1}
        },
        {
            {-1, -1, -1, -1},
            {2, 2, 2, -1},
            {-1, -1, 2, -1},
            {-1, -1, -1, -1}
        },
        {
            {-1, 2, -1, -1},
            {-1, 2, -1, -1},
            {2, 2, -1, -1},
            {-1, -1, -1, -1}
        }
    },
    { // L
        {
            {-1, -1, 3, -1},
            {3, 3, 3, -1},
            {-1, -1, -1, -1},
            {-1, -1, -1, -1}
        },
        {
            {-1, 3, -1, -1},
            {-1, 3, -1, -1},
            {-1, 3, 3, -1},
            {-1, -1, -1, -1}
        },
        {
            {-1, -1, -1, -1},
            {3, 3, 3, -1},
            {3, -1, -1, -1},
            {-1, -1, -1, -1}
        },
        {
            {3, 3, -1, -1},
            {-1, 3, -1, -1},
            {-1, 3, -1, -1},
            {-1, -1, -1, -1}
        }
    },
    { // T
        {
            {-1, 4, -1, -1},
            {4, 4, 4, -1},
            {-1, -1, -1, -1},
            {-1, -1, -1, -1}
        },
        {
            {-1, 4, -1, -1},
            {-1, 4, 4, -1},
            {-1, 4, -1, -1},
            {-1, -1, -1, -1}
        },
        {
            {-1, -1, -1, -1},
            {4, 4, 4, -1},
            {-1, 4, -1, -1},
            {-1, -1, -1, -1}
        },
        {
            {-1, 4, -1, -1},
            {4, 4, -1, -1},
            {-1, 4, -1, -1},
            {-1, -1, -1, -1}
        }
    },
    { // O
        {
            {-1, 5, 5, -1},
            {-1, 5, 5, -1},
            {-1, -1, -1, -1},
            {-1, -1, -1, -1}
        },
        {
            {-1, 5, 5, -1},
            {-1, 5, 5, -1},
            {-1, -1, -1, -1},
            {-1, -1, -1, -1}
        },
        {
            {-1, 5, 5, -1},
            {-1, 5, 5, -1},
            {-1, -1, -1, -1},
            {-1, -1, -1, -1}
        },
        {
            {-1, 5, 5, -1},
            {-1, 5, 5, -1},
            {-1, -1, -1, -1},
            {-1, -1, -1, -1}
        }
    },
    { // I
        {
            {-1, -1, -1, -1},
            {6, 6, 6, 6},
            {-1, -1, -1, -1},
            {-1, -1, -1, -1}
        },
        {
            {-1, -1, 6, -1},
            {-1, -1, 6, -1},
            {-1, -1, 6, -1},
            {-1, -1, 6, -1}
        },
        {
            {-1, -1, -1, -1},
            {-1, -1, -1, -1},
            {6, 6, 6, 6},
            {-1, -1, -1, -1}
        },
        {
            {-1, 6, -1, -1},
            {-1, 6, -1, -1},
            {-1, 6, -1, -1},
            {-1, 6, -1, -1}
        }
    }
};