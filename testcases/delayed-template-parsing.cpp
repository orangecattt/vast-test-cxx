// RUN: %driver -cc1 %isys -std=c++11 %s -fms-extensions -fdelayed-template-parsing %target -o %t%output-suffix && %filecheck

namespace ClassScopeSpecialization {
  struct Type {
    template <int i>
    void Foo() {}
    template <>
    void Foo<0>() {}
  };

  void call() {
    Type T;
// CHECK: call {{.*}} @"??$Foo@$0A@@Type@ClassScopeSpecialization@@QAEXXZ"
// X64: call {{.*}} @"??$Foo@$0A@@Type@ClassScopeSpecialization@@QEAAXXZ"
    T.Foo<0>();
  }
}
