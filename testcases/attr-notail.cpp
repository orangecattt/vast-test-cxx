// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

class Class1 {
public:
  [[clang::not_tail_called]] int m1();
  int m2();
  [[clang::not_tail_called]] virtual int m3();
  virtual int m4();
};

class Class2: public Class1 {
public:
  [[clang::not_tail_called]] int m4() override;
};

int foo1(int a, Class1 *c1, Class2 &c2) {
  if (a)
    return c1->m1();
  c1->m3();
  Class1 &c = c2;
  c.m4();
  c2.m4();
  return c1->m2();
}

