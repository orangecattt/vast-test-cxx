// RUN: %driver -cc1 %isys -fno-elide-constructors %s %target -o %t%output-suffix && %filecheck

int Bar(int);
int Baz(int);

int Func1(int x) {
  if (x) {
    [[clang::musttail]] return Bar(x);
  } else {
    [[clang::musttail]] return Baz(x); // CHECK: %call1 = musttail call noundef i32 @_Z3Bazi(i32 noundef %3)
  }
}

int Func2(int x) {
  {
    [[clang::musttail]] return Bar(Bar(x));
  }
}


class Foo {
public:
  static int StaticMethod(int x);
  int MemberFunction(int x);
  int TailFrom(int x);
  int TailFrom2(int x);
  int TailFrom3(int x);
};

int Foo::TailFrom(int x) {
  [[clang::musttail]] return MemberFunction(x);
}


int Func3(int x) {
  [[clang::musttail]] return Foo::StaticMethod(x);
}


int Func4(int x) {
  Foo foo; // Object with trivial destructor.
  [[clang::musttail]] return foo.StaticMethod(x);
}


int (Foo::*pmf)(int);

int Foo::TailFrom2(int x) {
  [[clang::musttail]] return ((*this).*pmf)(x);
}


int Foo::TailFrom3(int x) {
  [[clang::musttail]] return (this->*pmf)(x);
}


void ReturnsVoid();

void Func5() {
  [[clang::musttail]] return ReturnsVoid();
}


class HasTrivialDestructor {};

int ReturnsInt(int x);

int Func6(int x) {
  HasTrivialDestructor foo;
  [[clang::musttail]] return ReturnsInt(x);
}


struct Data {
  int (*fptr)(Data *);
};

int Func7(Data *data) {
  [[clang::musttail]] return data->fptr(data);
}


template <class T>
T TemplateFunc(T) {
  return 5;
}

int Func9(int x) {
  [[clang::musttail]] return TemplateFunc<int>(x);
}


template <class T>
int Func10(int x) {
  T t;
  [[clang::musttail]] return Bar(x);
}

int Func11(int x) {
  return Func10<int>(x);
}


template <class T>
T Func12(T x) {
  [[clang::musttail]] return ::Bar(x);
}

int Func13(int x) {
  return Func12<int>(x);
}


int Func14(int x) {
  int vla[x];
  [[clang::musttail]] return Bar(x);
}


void TrivialDestructorParam(HasTrivialDestructor obj);

void Func14(HasTrivialDestructor obj) {
  [[clang::musttail]] return TrivialDestructorParam(obj);
}


struct Struct3 {
  void ConstMemberFunction(const int *) const;
  void NonConstMemberFunction(int *i);
};
void Struct3::NonConstMemberFunction(int *i) {
  [[clang::musttail]] return ConstMemberFunction(i);
}


struct HasNonTrivialCopyConstructor {
  HasNonTrivialCopyConstructor(const HasNonTrivialCopyConstructor &);
};
HasNonTrivialCopyConstructor ReturnsClassByValue();
HasNonTrivialCopyConstructor TestNonElidableCopyConstructor() {
  [[clang::musttail]] return (((ReturnsClassByValue())));
}


struct HasNonTrivialCopyConstructor2 {
  HasNonTrivialCopyConstructor2(const HasNonTrivialCopyConstructor &, int DefaultParam = 5);
};
HasNonTrivialCopyConstructor2 ReturnsClassByValue2();
HasNonTrivialCopyConstructor2 TestNonElidableCopyConstructor2() {
  [[clang::musttail]] return (((ReturnsClassByValue2())));
}


void TestFunctionPointer(int x) {
  void (*p)(int) = nullptr;
  [[clang::musttail]] return p(x);
}


struct LargeWithCopyConstructor {
  LargeWithCopyConstructor(const LargeWithCopyConstructor &);
  char data[32];
};
LargeWithCopyConstructor ReturnsLarge();
LargeWithCopyConstructor TestLargeWithCopyConstructor() {
  [[clang::musttail]] return ReturnsLarge();
}


using IntFunctionType = int();
IntFunctionType *ReturnsIntFunction();
int TestRValueFunctionPointer() {
  [[clang::musttail]] return ReturnsIntFunction()();
}


void(FuncWithParens)() {
  [[clang::musttail]] return FuncWithParens();
}


int TestNonCapturingLambda() {
  auto lambda = []() { return 12; };
  [[clang::musttail]] return (+lambda)();
}


class TestVirtual {
  virtual void TailTo();
  virtual void TailFrom();
};

void TestVirtual::TailFrom() {
  [[clang::musttail]] return TailTo();
}

