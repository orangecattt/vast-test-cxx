// RUN: %driver -cc1 %isys %s -fms-extensions -stack-protector 2 %target -o %t%output-suffix && %filecheck

#pragma strict_gs_check(on)

extern "C" void test0() {
}



