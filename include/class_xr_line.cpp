#define FUNC 0
#define MOVR 10
#define MOVI 11
#define ARITHR 20
#define ARITHI 21
#define BL 3
#define BX 4
#define PUSH 5
#define POP 6
#include <fstream>
#include "class_xr_line.hpp"
#include "string_split.hpp"
#include "xr_auxiliary.hpp"

// Initialize an empty XrLine.
XrLine::XrLine() {
    this->func_name_ = "!none_func";
    this->label_ = "!none_label";
    this->opcode_ = "!none_opcode";
    this->rd_ = INT32_MAX;
    this->rn_ = INT32_MAX;
    this->op2_ = INT32_MAX;
    this->exit_reg_ = INT32_MAX;
    func_params_ = {};
    bl_params_ = {};
}

// Initialize an XrLine object with content.
XrLine::XrLine(string content) {
    this->func_name_ = "!none_func";
    this->label_ = "!none_label";
    this->opcode_ = "!none_opcode";
    this->rd_ = INT32_MAX;
    this->rn_ = INT32_MAX;
    this->op2_ = INT32_MAX;
    this->exit_reg_ = INT32_MAX;
    func_params_ = {};
    bl_params_ = {};
    this->init_line(content);
}

// Get the content of an xr or arm line.
string XrLine::get_content(void) {
    string res;
    if (this->line_type_ == FUNC) {
        res = func_name_ + ":";
    }
    else if (this->line_type_ == MOVR) {
        res = "  " + opcode_ + " #" + to_string(rd_) + ", #" + to_string(op2_);
    }
    else if (this->line_type_ == MOVI) {
        res = "  " + opcode_ + " #" + to_string(rd_) + ", " + to_string(op2_);
    }
    else if (this->line_type_ == ARITHR) {
        res = "  " + opcode_ + " #" + to_string(rd_) + ", " + to_string(rn_) +
              ", #" + to_string(op2_);
    }
    else if (this->line_type_ == ARITHI) {
        res = "  " + opcode_ + " #" + to_string(rd_) + ", " + to_string(rn_) +
              ", " + to_string(op2_);
    }
    else if (this->line_type_ == BL) {
        res = "  " + opcode_ + " " + label_;
    }
    else if (this->line_type_ == BX) {
        res = "  " + opcode_ + " lr";
    }
    return res;
}

// Initialize the type and fields of an xr line.
void XrLine::init_line(string input) {
    int res = INT32_MAX;
    vector<string> xr_line_split;
    string_split(input, " ", xr_line_split);
    if (xr_line_split[0] != "") {
        res = FUNC;
        this->func_name_ = get_init_func_name(input);
        this->func_params_ = get_init_func_params(input);
    }
    else if ((xr_line_split[2] == "add") || (xr_line_split[2] == "sub") ||
             (xr_line_split[2] == "mul") || (xr_line_split[2] == "div") ||
             (xr_line_split[2] == "and") || (xr_line_split[2] == "orr")) {
        string op2 = xr_line_split[5];
        if (op2.find("#") != op2.npos) {
            res = ARITHR;
        }
        else {
            res = ARITHI;
        }
        this->opcode_ = xr_line_split[2];
        this->rd_ = get_init_rd(xr_line_split);
        this->rn_ = get_init_rn(xr_line_split);
        this->op2_ = get_init_4_op2(xr_line_split);
    }
    else if (xr_line_split[2] == "mov") {
        string op2 = xr_line_split[4];
        if (op2.find("#") != op2.npos) {
            res = MOVR;
        }
        else {
            res = MOVI;
        }
        this->opcode_ = "mov";
        this->rd_ = get_init_rd(xr_line_split);
        this->op2_ = get_init_3_op2(xr_line_split);
    }
    else if (xr_line_split[2] == "bl") {
        res = BL;
        this->opcode_ = "bl";
        this->label_ = get_init_bl_label(input);
        this->bl_params_ = get_init_bl_params(input);
        this->exit_reg_ = get_init_bl_exit(input);
    }
    else if (xr_line_split[2] == "bx") {
        res = BX;
        this->opcode_ = "bx";
        this->exit_reg_ = get_init_bx_exit(input);
    }
    else if (xr_line_split[2] == "push") {
        res = PUSH;
        this->opcode_ = "push";
    }
    else if (xr_line_split[2] == "pop") {
        res = POP;
        this->opcode_ = "pop";
    }
    this->line_type_ = res;
}

// Output the line to a file.
// NOTE: The parameter must be an inference, or ArmFunc::out_xr_lines will go wrong.
void XrLine::out_line(ofstream& out) {
    string res;
    if (this->line_type_ == FUNC) {
        res = func_name_ + ":";
    }
    else if (this->line_type_ == MOVR) {
        res = "  " + opcode_ + " #" + to_string(rd_) + ", #" + to_string(op2_);
    }
    else if (this->line_type_ == MOVI) {
        res = "  " + opcode_ + " #" + to_string(rd_) + ", " + to_string(op2_);
    }
    else if (this->line_type_ == ARITHR) {
        res = "  " + opcode_ + " #" + to_string(rd_) + ", #" + to_string(rn_) +
              ", #" + to_string(op2_);
    }
    else if (this->line_type_ == ARITHI) {
        res = "  " + opcode_ + " #" + to_string(rd_) + ", #" + to_string(rn_) +
              ", " + to_string(op2_);
    }
    else if (this->line_type_ == BL) {
        res = "  " + opcode_ + " " + label_;
    }
    else if (this->line_type_ == BX) {
        res = "  " + opcode_ + " lr";
    }
    else if (this->line_type_ == PUSH || this->line_type_ == POP) {
        res = "  " + opcode_ + " {lr}";
    }
    out << res << endl;
}

// Get the name of the function.
string XrLine::get_func_name(void) {
    return this->func_name_;
}

// Get the bl label of a bl line.
string XrLine::get_bl_label(void) {
    return this->label_;
}

// Get the function parameters of the function.
vector<int> XrLine::get_func_params(void) {
    return this->func_params_;
}