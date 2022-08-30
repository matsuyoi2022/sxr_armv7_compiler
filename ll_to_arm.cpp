#include <iostream>
#include "include/ll_to_xr.hpp"
#include "include/xr_to_arm.hpp"
#include "include/xr_to_arm.hpp"
using namespace std;

int main(int argc, char *argv[]) {
    string ll_in = argv[1];
    int parent_pos = ll_in.find("llvm_ir") + 8;
    string file_body = ll_in.substr(parent_pos, ll_in.find(".") - parent_pos);
    string xr_suff = ".xr.s";
    string arm_suff = ".s";
    string xr_pref = "test/xr/";
    string arm_pref = "test/arm/";
    string xr_out = xr_pref + file_body + xr_suff;
    string arm_out = arm_pref + file_body + arm_suff;
    cout << "The result of our compiler is: " << arm_out << endl;
    ll_to_xr(ll_in, xr_out);
    xr_to_arm(xr_out, arm_out);
    return 0;
}