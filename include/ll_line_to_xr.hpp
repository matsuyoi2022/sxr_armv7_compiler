#ifndef LL_LINE_TO_XR_HPP
#define LL_LINE_TO_XR_HPP
#include <iostream>
#include "string_split.hpp"
#include "ll_auxiliary.hpp"
using namespace std;

// Turn an llvm ir line to an xr line.
void ll_line_to_xr(string& line) {
    vector<string> ll_line_split;
    regex arith("(add)|(sub)|(mul)|(sdiv)|(and)|(or)");
    if (line.find("store") != line.npos) {
        string_split(line, " ", ll_line_split);
        string ll_rd = ll_line_split[2];
        string ll_op2 = ll_line_split[1];
        line = "  mov " + ll_field_to_xr(ll_rd) + ", " + ll_field_to_xr(ll_op2);
    }
    else if (line.find("load") != line.npos) {
        string_split(line, " ", ll_line_split);
        string ll_rd = ll_line_split[0];
        string ll_op2 = ll_line_split[4];
        line = "  mov " + ll_field_to_xr(ll_rd) + ", " + ll_field_to_xr(ll_op2);
    }
    else if (regex_search(line, arith)) {
        string_split(line, " ", ll_line_split);
        string ll_arith = ll_line_split[2];
        string ll_rd = ll_line_split[0];
        string ll_rn = ll_line_split[3];
        string ll_op2 = ll_line_split[4];
        if (ll_arith == "or") {
            ll_arith = "orr";
        }
        line = "  " + ll_arith + " " + ll_field_to_xr(ll_rd) + ", " + ll_field_to_xr(ll_rn)
                + ", " + ll_field_to_xr(ll_op2);
    }
}
#endif