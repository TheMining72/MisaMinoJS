#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

std::vector<std::vector<std::string>> to_field(Napi::Array arr);
int clear_lines(std::vector<std::vector<std::string>>* board);
std::vector<std::string> split(std::string s, std::string delimiter);
extern const int* from_misamino;
extern const std::string to_char[7];
extern const std::string piece_defs[7][4][4][4];

#endif