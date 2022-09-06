#ifndef XR_AUXILIARY_HPP
#define XR_AUXILIARY_HPP
#include <iostream>
#include <vector>
#include "string_split.hpp"
using namespace std;

// Turn an xr parameter string to an integer vector.
// e.g. "#0, #1" -> {0, 1}
vector<int> xr_params_str_parser(string xr_params_str) {
    vector<string> xr_params_str_split = {};
    vector<int> res = {};
    string_split(xr_params_str, ", ", xr_params_str_split);
    for (auto i : xr_params_str_split) {
        res.push_back(atoi(i.c_str()));
    }
    return res;
}

#endif