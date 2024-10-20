// RUN: %driver -cc1 %isys %s
// RUN: %driver -cc1 %isys %s -std=c++98 %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s -std=c++11 %target -o %t%output-suffix && %filecheck
// expected-no-diagnostics

#if __cplusplus >= 201103L
// CHECK-CXX11: @_ZZ15InitRefWithListvE1r = internal constant ptr @_ZGRZ15InitRefWithListvE1r_
// CHECK-CXX11: @_ZGRZ15InitRefWithListvE1r_ = internal constant i32 123
int InitRefWithList() { static const int &r = {123}; return r; }
#endif

struct XPTParamDescriptor {};
struct nsXPTParamInfo {
  nsXPTParamInfo(const XPTParamDescriptor& desc);
};
void a(XPTParamDescriptor *params) {
  const nsXPTParamInfo& paramInfo = params[0];
}

// CodeGen of reference initialized const arrays.
namespace PR5911 {
  template <typename T, int N> int f(const T (&a)[N]) { return N; }
  int iarr[] = { 1 };
  int test() { return f(iarr); }
}

struct Foo { int foo; };
Foo& ignoreSetMutex = *(new Foo);

// Binding to a bit-field that requires a temporary. 
struct { int bitfield : 3; } s = { 3 };
const int &s2 = s.bitfield;

// In C++98, this forms a reference to itself. In C++11 onwards, this performs
// copy-construction.
struct SelfReference { SelfReference &r; };
extern SelfReference self_reference_1;
SelfReference self_reference_2 = {self_reference_1};
// CHECK-CXX98: @self_reference_2 = {{.*}}global %[[SELF_REF:.*]] { ptr @self_reference_1 }
// CHECK-CXX11: @self_reference_2 = {{(dso_local )?}}global %[[SELF_REF:.*]] zeroinitializer
// CHECK-CXX11: call {{.*}}memcpy{{.*}} @self_reference_2, {{.*}} @self_reference_1
