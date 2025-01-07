// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck




int __attribute__((target_clones("sse4.2", "default"))) overloaded(int) { return 1; }


int __attribute__((target_clones("arch=ivybridge", "default"))) overloaded(const char *) { return 2; }


void use_overloaded() {
  overloaded(1);
  overloaded(nullptr);
}

template<typename T, typename U>
struct C {
int __attribute__((target_clones("sse4.2", "default"))) foo(){ return 1;}
};
template<typename U>
struct C<int, U> {
int __attribute__((target_clones("sse4.2", "default"))) foo(){ return 2;}
};
template<typename U>
struct C<float, U> {
int foo(){ return 2;}
};
template<>
struct C<double, float> {
int __attribute__((target_clones("sse4.2", "default"))) foo(){ return 3;}
};

void uses_specialized() {
  C<short, short> c;
  c.foo();
  C<int, short> c2;
  c2.foo();
  C<float, short> c3;
  c3.foo();
  C<double, float> c4;
  c4.foo();
}








