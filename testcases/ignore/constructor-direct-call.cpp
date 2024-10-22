// RUN: %driver -cc1 %isys -fms-extensions -Wmicrosoft %s %target -o %t%output-suffix && %filecheck

class Test1 {
public:
   int a;
};

void f1() {
  Test1 var;
  var.Test1::Test1();

  var.Test1::Test1(var);
}

class Test2 {
public:
  Test2() { a = 10; b = 10; }
   int a;
   int b;
};

void f2() {
  Test2 var;

  var.Test2::Test2();

  var.Test2::Test2(var);
}




class Test3 {
public:
  Test3() { a = 10; b = 15; c = 20; }
  Test3(const Test3& that) { a = that.a; b = that.b; c = that.c; }
   int a;
   int b;
   int c;
};

void f3() {
  Test3 var;

  Test3 var2;

  var.Test3::Test3();

  var.Test3::Test3(var2);
}
