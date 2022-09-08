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
        int get_exit(void);
        vector<XrLine> get_lines(void);
        void out_xr_lines(ofstream& out);
        void push_xr_line(XrLine xr_line);
    private:
        string func_name_;
        vector<int> params_;
        vector<XrLine> xr_arm_lines_;
};

#endif