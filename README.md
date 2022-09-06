# 一个LLVM IR到ARMv7的编译器
## 1. 使用方法
```bash
mkdir out
g++ ll_to_arm.cpp include/class_arm_func.cpp include/class_xr_line.cpp -o out/sxr
./out/sxr ./test/llvm_ir/func.ll
# 随后可生成./test/xr/func.xr.s和./test/arm/func.ll.s
```