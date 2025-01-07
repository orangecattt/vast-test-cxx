// RUN: %driver -cc1 %isys -std=c++2a %s %target -o %t%output-suffix && %filecheck

struct TriviallyCopyable {};

struct NonTriviallyCopyable {
  NonTriviallyCopyable() = default;
  NonTriviallyCopyable(const NonTriviallyCopyable&) = default;
  NonTriviallyCopyable(NonTriviallyCopyable &&) {}
};

struct Foo {
  int i;
  [[no_unique_address]] TriviallyCopyable m;
  [[no_unique_address]] NonTriviallyCopyable n;
};

void call() {
  Foo foo;
  Foo foo2(static_cast<Foo&&>(foo));
}

