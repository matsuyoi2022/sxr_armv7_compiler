#ifndef XR_TO_ARM_HPP
#define XR_TO_ARM_HPP
#include <fstream>
#include <regex>
#include <set>
#include "string_split.hpp"
#include "class_xr_line.hpp"
#include "class_arm_func.hpp"
using namespace std;

void xr_to_arm(string& xr_in, string& arm_out) {
    ifstream in(xr_in);
    ofstream out(arm_out);

    regex xr_func_name("[[:alpha:]][[:graph:]]*:");
    regex xr_bx("^  bx");
    regex xr_bl("^  bl");
    regex xr_reg("#[[:digit:]]*");
    regex xr_global("^.global");

    string line;
    vector<ArmFunc> funcs;
    while (getline(in, line)) {
        XrLine xr_line_now(line);
        string xr_content = xr_line_now.get_content();
        if (regex_search(line, xr_func_name)) {
            string func_name = xr_line_now.get_func_name();
            vector<int> xr_params = xr_line_now.get_func_params();
            ArmFunc xr_func(func_name); // zpw
            funcs.push_back(xr_func);
            // (funcs.back()).set_arm_func_name(func_name);
            XrLine new_line(xr_line_now.get_func_name() + ":");
            (funcs.back()).push_xr_line(new_line);
        }
        else if (regex_search(line, xr_bx)) {
            (funcs.back()).push_xr_line(xr_line_now);
        }
        else if (regex_search(line, xr_bl)) {
            XrLine push_line("  push {lr}");
            XrLine pop_line("  pop {lr}");
            XrLine new_line("  bl " + xr_line_now.get_bl_label());
            (funcs.back()).push_xr_line(push_line);
            (funcs.back()).push_xr_line(new_line);
            (funcs.back()).push_xr_line(pop_line);
        }
        else if (regex_search(line, xr_reg)) {
            (funcs.back()).push_xr_line(xr_line_now);
        }
    }

    for (auto i : funcs) {
        i.out_xr_lines(out);
    }
}
#endif