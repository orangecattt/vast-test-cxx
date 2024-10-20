// RUN: %driver -cc1 %isys -fms-extensions %s %target -o %t%output-suffix && %filecheck


int __declspec(code_seg("foo_one")) bar_one(int) { return 1; }
int __declspec(code_seg("foo_two")) bar_one(int,float) { return 11; }
int __declspec(code_seg("foo_three")) bar_one(float) { return 12; }


struct __declspec(code_seg("my_one")) Base3 {
  virtual int barA(int) { return 1; }
  virtual int barA(int,float) { return 2; }
  virtual int barA(float) { return 3; }

  virtual void __declspec(code_seg("my_two")) barB(int) { }
  virtual void  __declspec(code_seg("my_three")) barB(float) { }
  virtual void __declspec(code_seg("my_four")) barB(int, float) { }

};


#pragma code_seg("another")
struct __declspec(code_seg("foo_four")) Foo {
  int bar3() {return 0;}
 __declspec(code_seg("foo_lala")) int bar4() {return 0;} }; int caller() {Foo f; return f.bar3() + f.bar4(); }


#pragma code_seg("something")

int __declspec(code_seg("foo")) bar1()
{
  int lala = 4;
  auto l = [=](int i) { return i+4; };
  return l(-4);
}


double __declspec(code_seg("foo")) bar2()
{
  double lala = 4.0;
  auto l = [=](double d) __declspec(code_seg("another"))  { return d+4.0; };
  return l(4.0);
}



