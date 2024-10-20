// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

// Make sure the call to b() doesn't get optimized out.
extern struct x {char& x,y;}y;
int b();      
int a() { if (!&y.x) b(); }

// CHECK: @_Z1bv
