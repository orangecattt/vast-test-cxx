// RUN: %driver -cc1 %isys < %s -fms-extensions -x c++ %target -o %t%output-suffix && %filecheck


__attribute__((optnone))
inline int func1(int a) {
  return a + a + a + a;
}

__attribute__((optnone))
int func2(int a);

inline int func2(int a) {
  return a + a + a + a;
}

int foo() {
  int val = func1(1);
  return val + func2(2);
}

__attribute__((optnone))
int func3(int a);

__attribute__((minsize))
int func3(int a) {
  return a + a + a + a;
}


__attribute__((noreturn))
extern void exit_from_function();

__attribute__((noreturn)) __attribute((optnone))
extern void noreturn_function(int a) { exit_from_function(); }


__declspec(noinline) __attribute__((optnone))
void func4() { return; }

__declspec(noinline)
extern void func5();

__attribute__((optnone))
void func5() { return; }



__attribute__((dllimport))
__attribute__((optnone))
int imported_optnone_func(int a);

__attribute__((dllexport))
__attribute__((optnone))
int exported_optnone_func(int a) {
  return imported_optnone_func(a); // use of imported func
}



