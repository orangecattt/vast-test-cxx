// RUN: %driver -cc1 %isys -std=c++98 -fno-elide-constructors %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++11 -fno-elide-constructors %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++98 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

// Reduced from PR12208
class X {
public:
  X();
  X(const X&);
#if __cplusplus >= 201103L
  X(X&&);
#endif
  ~X();
};

// CHECK-LABEL: define{{.*}} void @_Z4Testv(
X Test()
{
  X x;

  // Check that the copy constructor for X is called with result variable as
  // sret argument.
  // CHECK-CXX98: call void @_ZN1XC1ERKS_(
  // CHECK-CXX11: call void @_ZN1XC1EOS_(
  // CHECK-CXX98-ELIDE-NOT: call void @_ZN1XC1ERKS_(
  // CHECK-CXX11-ELIDE-NOT: call void @_ZN1XC1EOS_(

  // Make sure that the destructor for X is called.
  // FIXME: This call is present even in the -ELIDE runs, but is guarded by a
  // branch that is never taken in those cases. We could generate better IR
  // here.
  // CHECK: call void @_ZN1XD1Ev(
  return x;
}
