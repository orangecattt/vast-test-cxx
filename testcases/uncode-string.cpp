// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

wchar_t s[] = L"\u2722";

// CHECK: @s ={{.*}} global [2 x i32] [i32 10018, i32 0], align 4
