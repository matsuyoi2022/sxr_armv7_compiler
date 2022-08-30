#ifndef LL_LINE_PARSER_HPP
#define LL_LINE_PARSER_HPP
#include <iostream>
#include "string_split.hpp"
using namespace std;

// Turn an operator to a register of xr format if it is.
string to_reg(string ll_reg) {
    if (ll_reg[0] == '%') {
        string reg_num_str = ll_reg.substr(1);
        int reg_num = atoi(reg_num_str.c_str()) - 1;
        return "#" + to_string(reg_num);
    }
    else {
        return ll_reg;
    }
}

// Turn an llvm ir line to an xr line.
void ll_line_parser(string& line) {
    vector<string> ll_line_split;
    regex arith("(add)|(sub)|(mul)|(sdiv)|(and)|(or)");
    if (line.find("store") != line.npos) {
        string_split(line, " ", ll_line_split);
        string ll_rd = ll_line_split[2];
        string ll_op2 = ll_line_split[1];
        line = "  mov " + to_reg(ll_rd) + ", " + ll_op2.substr(0, ll_op2.length() - 1);
    }
    else if (line.find("load") != line.npos) {
        string_split(line, " ", ll_line_split);
        string ll_rd = ll_line_split[0];
        string ll_op2 = ll_line_split[4];
        line = "  mov " + to_reg(ll_rd) + ", " + to_reg(ll_op2);
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
        line = "  " + ll_arith + " " + to_reg(ll_rd) + ", " + to_reg(ll_rn)
                + ", " + to_reg(ll_op2);
    }
}
#endif