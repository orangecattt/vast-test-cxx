// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck
// Clang should not generate alias to available_externally definitions.
// Check that the destructor of Foo is defined.
// The destructors have different return type for different targets.
// CHECK: define linkonce_odr {{.*}} @_ZN3FooD2Ev
template <class CharT>
struct String {
  String() {}
  ~String();
};

template <class CharT>
inline __attribute__((visibility("hidden"), always_inline))
String<CharT>::~String() {}

extern template struct String<char>;

struct Foo : public String<char> { Foo() { String<char> s; } };

Foo f;
