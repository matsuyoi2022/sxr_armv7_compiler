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

// Get the initial rd of an xr line.
int get_init_rd(vector<string> xr_line_split) {
    int res = INT32_MAX;
    string xr_rd = xr_line_split[3].substr(1); // Delete the "#" in the front.
    int rd_len = xr_rd.length() - 1; // Delete the "," behind.
    res = atoi((xr_rd.substr(0, rd_len)).c_str());
    return res;
}

// Get the initial rn of an xr line.
int get_init_rn(vector<string> xr_line_split) {
    int res = INT32_MAX;
    string xr_rn = xr_line_split[4].substr(1); // Delete the "#" in the front.
    int rd_len = xr_rn.length() - 1; // Delete the "," behind.
    res = atoi((xr_rn.substr(0, rd_len)).c_str());
    return res;
}

// Get the initial op2 of a 4 field xr line.
int get_init_4_op2(vector<string> xr_line_split) {
    int res = INT32_MAX;
    string xr_op2 = xr_line_split[5];
    // Op2 will be a register if the field is begin with "#".
    if (xr_op2[0] == '#') {
        res = atoi((xr_op2.substr(1)).c_str());
    }
    else {
        res = atoi(xr_op2.c_str());
    }
    return res;
}

// Get the initial op2 of a 3 field xr line.
int get_init_3_op2(vector<string> xr_line_split) {
    int res = INT32_MAX;
    string xr_op2 = xr_line_split[4];
    // Op2 will be a register if the field is begin with "#".
    if (xr_op2[0] == '#') {
        res = atoi((xr_op2.substr(1)).c_str());
    }
    else {
        res = atoi(xr_op2.c_str());
    }
    return res;
}

// Get the initial function name of a function line.
string get_init_func_name(string input) {
    int colon_loc = input.find(":");
    string res = input.substr(0, colon_loc);
    return res;
}

// Get the initial label called in a bl line.
string get_init_bl_label(string input) {
    cout << input << endl; // zpw
    int bl_begin_loc = input.find("bl") + 4;
    int bl_end_loc = input.find("(") - 1;
    int label_name_len = bl_end_loc - bl_begin_loc + 1;
    string res = input.substr(bl_begin_loc, label_name_len);
    return res;
}

// Get the initial parameter vector of a function line.
vector<int> get_init_func_params(string input) {
    int colon_loc = input.find(":");
    vector<int> res = {};
    // If there are parameters in this function.
    if (input.length() > colon_loc + 1) {
        string params_str = input.substr(colon_loc + 2);
        res = xr_params_str_parser(params_str);
    }
    else {
        res = {};
    }
    return res;
}

// Get the initial parameter vector of a bl line.
vector<int> get_init_bl_params(string input) {
    int left_bracket_loc = input.find("(");
    int right_bracket_loc = input.find(")");
    int param_len = right_bracket_loc - left_bracket_loc - 1;
    vector<int> res = {};
    if (param_len >0) {
        string params_str = input.substr(left_bracket_loc + 1, param_len);
        res = xr_params_str_parser(params_str);
    }
    else {
        res = {};
    }
    return res;
}

#endif