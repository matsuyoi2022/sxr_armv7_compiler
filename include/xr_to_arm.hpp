#ifndef XR_TO_ARM_HPP
#define XR_TO_ARM_HPP
#include <fstream>
#include <regex>
#include <set>
#include "string_split.hpp"
using namespace std;

struct Func
{
    string func_name;
    int begin_line;
    int end_line;
    set<string> xr_reg_set;
};

void xr_to_arm(string& xr_in, string& arm_out) {
    ifstream in(xr_in);
    ofstream out(arm_out);

    regex xr_func_name(":$");
    regex xr_ret("^  bx");
    regex xr_reg("#[[:digit:]]*");

    string line;
    int line_no = 0;
    vector<Func> funcs;
    vector<string> xr_lines;
    while (getline(in, line)) {
        xr_lines.push_back(line);       
        if (regex_search(line, xr_func_name)) {
            // {} means an empty set.
            funcs.push_back({line, line_no, 0, {}});
        }
        else if (regex_search(line, xr_ret)) {
            Func &xr_func_now = funcs.back();
            xr_func_now.end_line = line_no;
        }
        else if (regex_search(line, xr_reg)) {
            string reg_name;
            Func &xr_func_now = funcs.back();
            for (int i = 0; i < line.length(); i++){
                if (line[i] == '#') {
                    for (int j = i+1; j < line.length(); j++) {
                        if (line[j] < '0' or line[j] > '9') {
                            reg_name = line.substr(i, j - i);
                            (xr_func_now.xr_reg_set).insert(reg_name);
                            // Jump out if we find the end of the reg.
                            break;
                        }
                    }
                }
            }
        }
        line_no ++;
    }

    for (auto f : funcs) {
        cout << f.func_name << " " << f.begin_line
        << " " << f.end_line << " " << (f.xr_reg_set).size() << endl;
    }

    for (auto f : funcs) {
        string &before_end_line = xr_lines[f.end_line - 1];
        vector<string> xr_line_split;
        string_split(before_end_line, " ", xr_line_split);
        if (xr_line_split.size() == 5) {
            string xr_op2 = xr_line_split[4];
            before_end_line = "  " + xr_line_split[2] + " #0, " + xr_op2;
        }
        else if (xr_line_split.size() == 6) {
            string xr_rn = xr_line_split[4];
            string xr_op2 = xr_line_split[5];
            before_end_line = "  " + xr_line_split[2] + " #0, " + xr_rn
            + " " + xr_op2;
        }
    }
    
    for (auto l : xr_lines) {
        out << l << endl;
    }
}
#endif