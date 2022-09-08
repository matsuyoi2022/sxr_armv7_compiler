#ifndef CLASS_XR_LINE_HPP
#define CLASS_XR_LINE_HPP
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class XrLine {
    public:
        XrLine();
        XrLine(string content);
        string get_content(void);
        void init_line(string input);
        void out_line(ofstream& out);
        string get_func_name(void);
        string get_bl_label(void);
        vector<int> get_func_params(void);
    private:
        string func_name_;
        string label_;
        string opcode_;
        int line_type_;
        int rd_;
        int rn_;
        int op2_;
        int exit_reg_;
        vector<int> func_params_;
        vector<int> bl_params_;
};
#endif