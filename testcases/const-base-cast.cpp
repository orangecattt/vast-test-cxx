// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

// Check that the following construct, which is similar to one which occurs
// in Firefox, is folded correctly.
struct A { char x; };
struct B { char y; };
struct C : A,B {};
unsigned char x = ((char*)(B*)(C*)0x1000) - (char*)0x1000;

// CHECK: @x = {{(dso_local )?}}global i8 1
