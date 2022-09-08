#include "class_arm_func.hpp"
#include "string_split.hpp"

// Initialize an empty ArmFunc object.
ArmFunc::ArmFunc() {
    func_name_ = "!!!none";
    params_ = {};
    xr_arm_lines_ = {};
}

// Initialize an ArmFunc object with a function name.
ArmFunc::ArmFunc(string func_name) {
    func_name_ = func_name;
    params_ = {};
    xr_arm_lines_ = {};
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

// Append an xr line.
void ArmFunc::push_xr_line(XrLine xr_line) {
    (this->xr_arm_lines_).push_back(xr_line);
}

// Get the exit register of the function.
int ArmFunc::get_exit(void) {
    XrLine last_line = (this->xr_arm_lines_).back();
}