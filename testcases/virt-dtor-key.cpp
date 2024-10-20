// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
// CHECK: @_ZTI3foo ={{.*}} constant
// CHECK-MINGW: @_ZTI3foo = linkonce_odr
class foo {
   foo();
   virtual ~foo();
};

foo::~foo() {
}
