#ifndef LL_TO_XR_HPP
#define LL_TO_XR_HPP
#include <fstream>
#include <regex>
#include "ll_line_to_xr.hpp"
#include "ll_auxiliary.hpp"
using namespace std;

void ll_to_xr(string& ll_in, string& xr_out) {
    ifstream in(ll_in);
    ofstream out(xr_out);

    // Use two layers of brackets to enable escape characters.
    regex ll_content("[[:graph:]]|}");
    regex ll_no_use("^(!|;|s|t|a)");
    regex ll_func_end("}");
    regex ll_mov("(store)|(load)");
    regex ll_def("define dso_local");
    regex ll_ret("[[:blank:]]*ret");
    regex ll_call("= call ");
    regex ll_arith("(add)|(sub)|(mul)|(sdiv)|(and)|(or)");
    
    string line;
    // out << ".global main" << endl;
    while (getline(in, line)) {
        if (!regex_search(line, ll_content)) {
            ;
        }
        else if (regex_search(line, ll_no_use)) {
            ;       
        }
        else if(regex_search(line, ll_func_end)) {
            ;
        }
        else if (regex_search(line, ll_def)) {
            int func_end_loc = line.find("(") - 1;
            int param_end_loc = line.find(")") - 1;
            int params_len = param_end_loc - func_end_loc - 1;
            string func_name = ll_func_name_to_xr(line.substr(0, func_end_loc + 1));
            if (params_len > 0) {
                string ll_params = line.substr(func_end_loc + 2, params_len);
                string xr_params = ll_params_to_xr(ll_params);
                out << func_name << ": " << xr_params << endl;
            }
            else {
                out << func_name << ":" << endl;
            }
        }
        else if (regex_search(line, ll_ret)) {
            out << "  bx lr" << endl;
        }
        else if (regex_search(line, ll_call)) {
            int func_end_loc = line.find("(") - 1;
            int param_end_loc = line.find(")") - 1;
            int params_len = param_end_loc - func_end_loc - 1;
            int equal_loc = line.find("=");
            string func_name = ll_func_name_to_xr(line.substr(0, func_end_loc + 1));
            string target_reg = ll_field_to_xr(line.substr(2, equal_loc + 1));
            if (params_len > 0) {
                string ll_params = line.substr(func_end_loc + 2, params_len);
                string xr_params = ll_params_to_xr(ll_params);
                out << "  bl @" << func_name << "(" << xr_params << ")" <<
                 " -> " << target_reg <<endl;
            }
            else {
                out << "  bl @" << func_name << " ->" << target_reg << endl;
            }
        }
        else if(regex_search(line, ll_mov)) {
            string new_line;
            int align_loc = line.find(", align 4");
            int i32p_loc = line.find("i32*");
            int i32_loc = line.find("i32");
            new_line = line.replace(align_loc, 10, "");
            new_line = new_line.replace(i32p_loc, 5, "");
            new_line = new_line.replace(i32_loc, 4, "");
            new_line = new_line.substr(2);
            ll_line_to_xr(new_line);
            out << new_line << endl;
        }
        else if (regex_search(line, ll_arith)) {
            string new_line;
            int nsw_loc = line.find("nsw");
            int i32_loc = line.find("i32");
            if (nsw_loc != line.npos) {
                new_line = line.replace(nsw_loc, 4, "");
                i32_loc -= 4;
            }
            if (i32_loc != line.npos) {
                new_line = line.replace(i32_loc, 4, "");
            }
            new_line = line.substr(2);
            ll_line_to_xr(new_line);
            out << new_line << endl;
        }
    }
    in.close();
    out.close();
}
#endif