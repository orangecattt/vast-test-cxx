// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck
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
