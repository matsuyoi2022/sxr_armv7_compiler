#ifndef CLASS_XR_LINE_HPP
#define CLASS_XR_LINE_HPP
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class XrLine {
    public:
        XrLine(string content);
        XrLine(string content, int line_no);
        string get_content(void);
        string get_type(void);
        int get_line_no(void);
        int get_rd(void);
        int get_rn(void);
        pair<bool, string> get_op2(void);
        string get_func_name(void);
        string get_called_name(void);
        vector<int> get_func_params(void);
        vector<int> get_called_params(void);
        void out_line(ofstream& out);
        void set_line_no(int new_line_no);
        void set_rd(int new_rd);
        void set_rn(int new_rn);
        void set_op2(string new_op2);
        void set_params(vector<int> new_params);

    private:
        string xr_line_;
        int line_no_;
};
#endif