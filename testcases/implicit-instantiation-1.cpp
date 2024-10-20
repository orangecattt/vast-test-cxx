// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

template<typename T>
struct X {
  void f(T) { }
  void f(char) { }
  
  void g(T) { }
  
  void h(T) { }
};

void foo(X<int> &xi, X<float> *xfp, int i, float f) {
  xi.f(i);
  
  xi.g(f);
  
  xfp->f(f);
  
  
}



