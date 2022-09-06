#include "class_arm_func.hpp"
#include "string_split.hpp"

// Initialize an empty ArmFunc object.
ArmFunc::ArmFunc() {
    func_name_ = "!!!none";
    params_ = {};
    xr_arm_lines_ = {};
    xr_begin_line_ = 0;
    xr_end_line_ = 0;
    arm_begin_line_ = 0;
    arm_begin_line_ = 0;
}

// Initialize an ArmFunc object with a function name.
ArmFunc::ArmFunc(string func_name) {
    func_name_ = func_name;
    params_ = {};
    xr_arm_lines_ = {};
    xr_begin_line_ = 0;
    xr_end_line_ = 0;
    arm_begin_line_ = 0;
    arm_begin_line_ = 0;
}

// Get the name of the function.
string ArmFunc::get_arm_func_name(void) {
    return this->func_name_;
}

// Get all the lines of the function.
vector<XrLine> ArmFunc::get_lines(void) {
    return this->xr_arm_lines_;
}

// Output lines to a file
// NOTE: The parameter must be an inference, or it will go wrong.
void ArmFunc::out_xr_lines(ofstream& out) {
    for (auto i : this->xr_arm_lines_) {
        i.out_line(out);
    }
}

// Append an xr line..
void ArmFunc::push_xr_line(XrLine xr_line) {
    (this->xr_arm_lines_).push_back(xr_line);
    // cout << xr_line.get_content() << "NOOO" << endl; // zpw OK
    // cout << ((this->xr_arm_lines_).back()).get_content() << "///" << endl; // zpw OK
}

// Determine the name of the function.
void ArmFunc::set_arm_func_name(string func_name) {
    this->func_name_ = func_name;
}

// Set the parameters of a function.
void ArmFunc::set_params(vector<int> xr_params) {
    this->params_ = xr_params;
}

// Determine the begin line number in xr file.
void ArmFunc::set_xr_begin_line(XrLine xr_begin_line) {
    this->xr_begin_line_ = xr_begin_line.get_line_no();
}

// Determine the end line number in xr file.
void ArmFunc::set_xr_end_line(XrLine xr_end_line) {
    this->xr_begin_line_ = xr_end_line.get_line_no();
}