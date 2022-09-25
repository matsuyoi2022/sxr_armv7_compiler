#ifndef CLASS_XR_LINE_HPP
#define CLASS_XR_LINE_HPP
#define FUNC 0
#define MOVR 10
#define MOVI 11
#define ARITHR 20
#define ARITHI 21
#define BL 3
#define BX 4
#define PUSH 5
#define POP 6
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class XrLine {
    public:
        XrLine();
        XrLine(string content);
        void init_line(string input);
        void out_line(ofstream& out);
        string get_content(void);
        int get_line_type(void);
        int get_rd(void);
        int get_rn(void);
        int get_op2(void);
        int get_exit_reg(void);
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