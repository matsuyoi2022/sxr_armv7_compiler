#ifndef LL_AUXILIARY_HPP
#define LL_AUXILIARY_HPP
#include <iostream>
#include <vector>
#include "string_split.hpp"
using namespace std;

// Turn an llvm ir field to a register of xr/arm format if it is.
// The filed may be a register or an immediate number.
// e.g. "%0," -> "#0", "1" -> "1"
string ll_field_to_xr(string ll_field) {
    if (ll_field[0] == '%') {
        string reg_num_str = ll_field.substr(1);
        int reg_num = atoi(reg_num_str.c_str());
        return "#" + to_string(reg_num);
    }
    else {
        int imm_num = atoi(ll_field.c_str());
        return to_string(imm_num);
    }
}

// Turn an llvm ir function name string to the form of xr.
// e.g. "define dso_local i32 @func" -> "func"
string ll_func_name_to_xr(string ll_func) {
    int at_loc = ll_func.find("@");
    int end_loc = ll_func.length() - 1;
    int func_name_len = end_loc - at_loc;
    string res = ll_func.substr(at_loc + 1, func_name_len);
    return res;
}

// Turn an llvm ir parameter string to the form of xr.
// e.g. "i32 %0, i32 %1" -> "#0, #1"
string ll_params_to_xr(string ll_params) {
    int i32_loc = ll_params.find("i32 %");
    while (i32_loc != ll_params.npos) {
         ll_params.replace(i32_loc, 5, "#");
         i32_loc = ll_params.find("i32 %");
    }
    return ll_params;
}

#endif