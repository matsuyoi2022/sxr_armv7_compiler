#ifndef XR_TO_ARM_HPP
#define XR_TO_ARM_HPP
#include <fstream>
#include <regex>
#include "string_split.hpp"
using namespace std;

struct Func
{
    string func_name;
    unsigned int begin_line;
    unsigned int end_line;
    vector<unsigned int> call_lines;
};

void xr_to_arm(string& xr_in, string& arm_out) {
    ifstream in(xr_in);
    ofstream out(arm_out);

    regex xr_func_name(":$");
    regex xr_ret("^  bx");

    string line;
    unsigned int line_no = 0;
    vector<Func> funcs;
    vector<string> xr_lines;
    while (getline(in, line)) {
        xr_lines.push_back(line);       
        if (regex_search(line, xr_func_name)) {
            // cout << line_no <<" ok" << endl;
            funcs.push_back({line, line_no, 0});
        }
        else if (regex_search(line, xr_ret)) {
            // cout << funcs.size() << endl;
            Func &xr_func = funcs.back();
            xr_func.end_line = line_no;
        }
        line_no ++;
    }

    for (auto f : funcs) {
        cout << f.func_name << " " << f.begin_line
        << " " << f.end_line << endl;
    }

    for (auto f : funcs) {
        string &before_end_line = xr_lines[f.end_line - 1];
        vector<string> xr_line_split;
        string_split(before_end_line, " ", xr_line_split);
/*         
        for (auto s : xr_line_split) {
            cout << "***" << s << endl;
        }
         */
        string xr_op2 = xr_line_split[4];
        before_end_line = "  " + xr_line_split[2] + " #0, " + xr_op2;
    }
    
    for (auto l : xr_lines) {
        out << l << endl;
    }
}
#endif
/* 
int main() {
    string in = "assign.xr.s";
    string out = "assign.s";
    xr_to_arm(in, out);
    return 0;
} */
/* assign.xr.x
.global main
main:
  mov #1, 0
  mov #2, 5
  mov #3, #2
  bx lr
 */
