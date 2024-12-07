// RUN: %driver -cc1 %isys -fexceptions -fcxx-exceptions -std=c++1z %s %target -o %t%output-suffix && %filecheck

void *builtin_new(unsigned long n) { return __builtin_operator_new(n); }

void builtin_delete(void *p) { return __builtin_operator_delete(p); }
