// RUN: %driver -cc1 %isys -std=c++2a %s %target -o %t%output-suffix && %filecheck



extern thread_local int a;
extern thread_local constinit int b;

int get_a() { return a; }


int get_b() { return b; }


extern thread_local int c;

int get_c() { return c; }


thread_local int c = 0;


extern thread_local constinit struct DestructedFwdDecl e3;
DestructedFwdDecl &get_e3() { return e3; }

int d_init();

thread_local int d = d_init();

struct Destructed {
  int n = 0;
  ~Destructed();
};

extern thread_local constinit Destructed e;
int get_e() { return e.n; }

thread_local constinit Destructed e2;

thread_local constinit int f = 4;


struct NotDestructed { int n = 0; };
thread_local constinit NotDestructed nd;
