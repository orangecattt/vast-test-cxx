// Sparc64 is used because AArch64 and X86_64 would both use musttail.
// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
// Crasher for PR22929.
class Base {
  virtual void VariadicFunction(...);
};

class Derived : public virtual Base {
  virtual void VariadicFunction(...);
};

void Derived::VariadicFunction(...) { }

// CHECK: define{{.*}} void @_ZN7Derived16VariadicFunctionEz({{.*}} !dbg ![[SP:[0-9]+]]
// CHECK: ret void, !dbg ![[LOC:[0-9]+]]
// CHECK: define{{.*}} void @_ZT{{.+}}N7Derived16VariadicFunctionEz({{.*}} !dbg ![[SP_I:[0-9]+]]
// CHECK: ret void, !dbg ![[LOC_I:[0-9]+]]
//
// CHECK: ![[SP]] = distinct !DISubprogram(name: "VariadicFunction"
// CHECK: ![[LOC]] = !DILocation({{.*}}scope: ![[SP]])
// CHECK: ![[SP_I]] = distinct !DISubprogram(name: "VariadicFunction"
// CHECK: ![[LOC_I]] = !DILocation({{.*}}scope: ![[SP_I]])
