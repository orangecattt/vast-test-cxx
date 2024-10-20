// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

// Check that PR17480 is fixed: __attribute__((used)) ignored in templated
// classes
namespace InstantiateUsedMemberDefinition {
template <typename T>
struct S {
  int __attribute__((used)) f() {
    return 0;
  }
};

void test() {
  // Check that InstantiateUsedMemberDefinition::S<int>::f() is defined
  // as a result of the S class template implicit instantiation
  // CHECK: define linkonce_odr noundef i32 @_ZN31InstantiateUsedMemberDefinition1SIiE1fEv
  S<int> inst;
}
} // namespace InstantiateUsedMemberDefinition
