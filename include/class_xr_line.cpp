#define OP_REG false
#define OP_IMM true
#include <fstream>
#include "class_xr_line.hpp"
#include "string_split.hpp"
#include "xr_auxiliary.hpp"

// Initialize an XrLine object.
XrLine::XrLine(string content, int line_no) {
    this->xr_line_ = content;
    this->line_no_ = line_no;
}

// Initialize an XrLine object.
XrLine::XrLine(string content) {
    this->xr_line_ = content;
}

// Get the content of an xr or arm line.
string XrLine::get_content(void) {
    // "return xr_line_" is also OK.
    return this->xr_line_;
}

// Get the type of an xr or arm line.
// 0: func, 1: arith, 2: mov, 3: bl, 4: bx;
string XrLine::get_type(void) {
    string res = "none";
    vector<string> xr_line_split;
    string_split(xr_line_, " ", xr_line_split);
    if (xr_line_split[0] != "") {
        res = "func";
    }
    else if ((xr_line_split[2] == "add") || (xr_line_split[2] == "sub") ||
             (xr_line_split[2] == "mul") || (xr_line_split[2] == "div") ||
             (xr_line_split[2] == "and") || (xr_line_split[2] == "orr")) {
        res = "arith";
    }
    else if (xr_line_split[2] == "mov") {
        res = "mov";
    }
    else if (xr_line_split[2] == "bl") {
        res = "bl";
    }
    else if (xr_line_split[2] == "bx") {
        res = "bx";
    }
    return res;
}

// Get the line number of an xr or arm line.
int XrLine::get_line_no(void) {
    return this->line_no_;
}

// Get the rd field of an xr line.
int XrLine::get_rd(void) {
    int res = -1;
    if ((this->get_type() != "arith") && (this->get_type() != "mov")) {
        cout << "There is no rd in this line!" << endl;
        return res;
    }
    vector<string> xr_line_split;
    string_split(xr_line_, " ", xr_line_split);
    string xr_rd = xr_line_split[3].substr(1); // Delete the "#" in the front.
    int rd_len = xr_rd.length() - 1; // Delete the "," behind.
    res = atoi((xr_rd.substr(0, rd_len)).c_str());
    return res;
}

// Get the rn field of an xr line.
int XrLine::get_rn(void) {
    int res = -1;
    if (this->get_type() != "arith") {
        cout << "There is no rn in this line!" << endl;
        return res;
    }
    vector<string> xr_line_split;
    string_split(xr_line_, " ", xr_line_split);
    string xr_rn = xr_line_split[4].substr(1); // Delete the "#" in the front.
    int rn_len = xr_rn.length() - 1; // Delete the "," behind.
    res = atoi((xr_rn.substr(0, rn_len)).c_str());
    return res;
}

// Get the op2 field of an xr line.
// The first element is 0 if op2 is a reg, 1 if op2 is a imm.
pair<bool, string> XrLine::get_op2(void) {
    pair<bool, string> res;
    if ((this->get_type() != "arith") && (this->get_type() != "mov")) {
        res.first = 0;
        res.second = "!!!none";
        cout << "There is no op2 in this line!" << endl;
        return res;
    }
    vector<string> xr_line_split;
    string_split(xr_line_, " ", xr_line_split);
    string xr_op2 = xr_line_split[5];
    // Op2 will be a register if the field is begin with "#".
    if (xr_op2[0] == '#') {
        res.first = OP_REG;
    }
    else {
        res.first = OP_IMM;
    }
    res.second = xr_op2;
    return res;
}

// Get the function name of a function line.
string XrLine::get_func_name(void) {
    if (this->get_type() != "func") {
        cout << "This is not a function line!" << endl;
        return "!!!none";
    }
    int colon_loc = (this->xr_line_).find(":");
    string res = (this->xr_line_).substr(0, colon_loc);
    return res;
}

// Get the parameters of a bl(calling) line.
string XrLine::get_called_name(void) {
    if (this->get_type() != "bl") {
        cout << "This is not a bl line!" << endl;
        return "!!!none";
    }
    int bl_begin_loc = (this->xr_line_).find("bl") + 4;
    int bl_end_loc = (this->xr_line_).find("(") - 1;
    int func_name_len = bl_end_loc - bl_begin_loc + 1;
    string res = (this->xr_line_).substr(bl_begin_loc, func_name_len);
    return res;
}

// Get the parameter vector of a function line.
vector<int> XrLine::get_func_params(void) {
    if (this->get_type() != "func") {
        cout << "This is not a function line!" << endl;
        return {};
    }
    int colon_loc = (this->xr_line_).find(":");
    vector<int> res = {};
    if ((this->xr_line_).length() > colon_loc + 1) {
        string params_str = (this->xr_line_).substr(colon_loc + 2);
        vector<int> res = xr_params_str_parser(params_str);
    }
    else {
        string func_name = this->get_func_name();
    }
    return res;
}

// Output the line to a file.
// NOTE: The parameter must be an inference, or ArmFunc::out_xr_lines will go wrong.
void XrLine::out_line(ofstream& out) {
    out << this->xr_line_ << endl;
    // cout << this->xr_line_ << "$$$" << endl; // zpw
}