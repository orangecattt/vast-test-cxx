// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

template <class T> struct A { A(); };
struct B { A<int> x; };
void a() {   
  B b;
}

