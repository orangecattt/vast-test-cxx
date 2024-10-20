// RUN: %driver -cc1 %isys -fms-extensions %s %target -o %t%output-suffix && %filecheck


int __declspec(code_seg("foo_one")) bar_one() { return 1; }

#pragma code_seg("foo_two")
int __declspec(code_seg("foo_three")) bar2() { return 2; }

int another1() { return 1001; }


struct __declspec(code_seg("foo_four")) Foo {
  int bar3() {return 0;}
  int bar4();
  int __declspec(code_seg("foo_six")) bar6() { return 6; }
  int bar7() { return 7; }
  struct Inner {
    int bar5() { return 5; }
  } z;
  virtual int baz1() { return 1; }
};

struct __declspec(code_seg("foo_four")) FooTwo : Foo {
  int baz1() { return 20; }
};

int caller1() {
  Foo f; return f.bar3();
}

int Foo::bar4() { return 4; }

#pragma code_seg("someother")

int caller2() {
  Foo f;
  Foo *fp = new FooTwo;
  return f.z.bar5() + f.bar6() + f.bar7() + fp->baz1();
}

#pragma code_seg(push,"AnotherSeg")

struct FooThree {
  int bar8();
  int bar9() { return 9; }
};

#pragma code_seg(pop)


int FooThree::bar8() {return 0;}

int caller3()
{
  FooThree f;
  return f.bar8() + f.bar9();
}


struct NonTrivialCopy {
  NonTrivialCopy();
  NonTrivialCopy(const NonTrivialCopy&);
  ~NonTrivialCopy();
};


struct __declspec(code_seg("foo_seven")) FooFour {
  FooFour() {}
  int __declspec(code_seg("foo_eight")) bar10(int t) { return t; }
  NonTrivialCopy f;
};


struct FooFive {
  FooFive() {}
  int __declspec(code_seg("foo_nine")) bar11(int t) { return t; }
  NonTrivialCopy f;
};


#pragma code_seg("YetAnother")
int caller4()
{
  FooFour z1;
  FooFour z2 = z1;
  FooFive y1;
  FooFive y2 = y1;
 return z2.bar10(0) + y2.bar11(1);
}


struct FooSix {
  #pragma code_seg("foo_ten")
  int bar12() { return 12; }
  #pragma code_seg("foo_eleven")
  int bar13() { return 13; }
};

int bar14() { return 14; }

int caller5()
{
  FooSix fsix;
  return fsix.bar12() + fsix.bar13();
}


