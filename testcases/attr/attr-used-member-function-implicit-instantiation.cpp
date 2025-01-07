// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

namespace InstantiateUsedMemberDefinition {
template <typename T>
struct S {
  int __attribute__((used)) f() {
    return 0;
  }
};

void test() {
  S<int> inst;
}
} // namespace InstantiateUsedMemberDefinition
