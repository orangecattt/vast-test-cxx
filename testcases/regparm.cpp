// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck


// CHECK: _Z3fooRi(ptr inreg
void __attribute__ ((regparm (1)))  foo(int &a) {
}

struct S1 {
  int x;
  S1(const S1 &y);
};

void __attribute__((regparm(3))) foo2(S1 a, int b);
// CHECK: declare void @_Z4foo22S1i(ptr inreg noundef, i32 inreg noundef)
void bar2(S1 a, int b) {
  foo2(a, b);
}

struct S2 {
  int x;
};

void __attribute__((regparm(3))) foo3(struct S2 a, int b);
// CHECK: declare void @_Z4foo32S2i(i32 inreg, i32 inreg noundef)
void bar3(struct S2 a, int b) {
  foo3(a, b);
}

struct S3 {
  struct {
    struct {} b[0];
  } a;
};
__attribute((regparm(2))) void foo4(S3 a, int b);
// CHECK: declare void @_Z4foo42S3i(ptr noundef byval(%struct.S3) align 4, i32 inreg noundef)
void bar3(S3 a, int b) {
  foo4(a, b);
}