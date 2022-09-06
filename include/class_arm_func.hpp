#ifndef CLASS_ARM_FUNC_HPP
#define CLASS_ARM_FUNC_HPP
#include <iostream>
#include "class_xr_line.hpp"
using namespace std;

class ArmFunc {
    public:
        ArmFunc();
        ArmFunc(string func_name);
        string get_arm_func_name(void);
        vector<XrLine> get_lines(void);
        void out_xr_lines(ofstream& out);
        void push_xr_line(XrLine xr_line);
        void set_arm_func_name(string func_name);
        void set_params(vector<int> xr_params);
        void set_xr_begin_line(XrLine xr_begin_line);
        void set_xr_end_line(XrLine xr_end_line);
    private:
        string func_name_;
        vector<int> params_;
        vector<XrLine> xr_arm_lines_;
        int xr_begin_line_;
        int xr_end_line_;
        int arm_begin_line_;
        int amr_end_line_;
};

#endif