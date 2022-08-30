#ifndef LL_TO_XR_HPP
#define LL_TO_XR_HPP
#include <fstream>
#include <regex>
#include "ll_line_parser.hpp"
using namespace std;

void ll_to_xr(string& ll_in, string& xr_out) {
    ifstream in(ll_in);
    ofstream out(xr_out);

    regex ll_content("[:graph:]|}");
    regex ll_no_use("^(!|;|s|t|a)");
    regex ll_func_end("}");
    regex ll_mov("(store)|(load)");
    regex ll_def("define dso_local");
    regex ll_ret("[[:blank:]]*ret");
    regex ll_call("= call ");
    regex ll_add("add");
    
    string line;
    string func_name;
    out << ".global main" << endl;
    while (getline(in, line)) {
        if(!regex_search(line, ll_content)) {
            // out << "non" << endl;
        }
        else if(regex_search(line, ll_no_use)) {
            // out << "no use" << endl;        
        }
        else if(regex_search(line, ll_func_end)) {
            // out << "func_end" << endl;
        }
        else if(regex_search(line, ll_def)) {
            int begin_loc = line.find(" @") + 2;
            int end_loc = line.find("()") - 1;
            func_name = line.substr(begin_loc, end_loc - begin_loc  + 1);
            out << func_name << ":" << endl;
        }
        else if(regex_search(line, ll_ret)) {
            out << "  bx lr" << endl;
        }
        else if(regex_search(line, ll_call)) {
            int begin_loc = line.find(" @") + 2;
            int end_loc = line.find("()") - 1;
            func_name = line.substr(begin_loc, end_loc - begin_loc + 1);
            out << "  bl " << func_name << endl;
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
            ll_line_parser(new_line);
            out << new_line << endl;
        }
        else if (regex_search(line, ll_add)) {
            string new_line;
            int nsw_loc = line.find("nsw i32");
            new_line = line.replace(nsw_loc, 8, "");
            new_line = line.substr(2);
            ll_line_parser(new_line);
            out << new_line << endl;
        }
    }
    in.close();
    out.close();
}
#endif