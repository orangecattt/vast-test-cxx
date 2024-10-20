// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
// expected-no-diagnostics

bool a() { return __is_pod(int); }

bool b() { return __is_trivially_constructible(int, int, int); }
