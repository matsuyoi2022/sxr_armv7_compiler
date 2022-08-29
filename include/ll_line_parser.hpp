#ifndef LL_LINE_PARSER_HPP
#define LL_LINE_PARSER_HPP
#include <iostream>
#include "string_split.hpp"
using namespace std;

string mov = "mov";
string space = " ";
string comma = ",";
string sharp = "#";
string to_reg(string ll_reg) {
    return sharp + ll_reg.substr(1);
}

void ll_line_parser(string& line) {
    vector<string> ll_line_split;
    if (line.find("store") != line.npos) {
        string_split(line, " ", ll_line_split);
        string ll_rd = ll_line_split[2];
        string ll_op2 = ll_line_split[1];
        /*
        for(auto i: ll_line_split)
            cout << "***" << i << endl;
        */
        line = "  mov " + to_reg(ll_rd) + ", " + ll_op2.substr(0, ll_op2.length() - 1);
    }
    else if (line.find("load") != line.npos) {
        string_split(line, " ", ll_line_split);
        string ll_rd = ll_line_split[0];
        string ll_op2 = ll_line_split[4];
        line = "  mov "+ to_reg(ll_rd) + ", " + to_reg(ll_op2);
    }
}
#endif