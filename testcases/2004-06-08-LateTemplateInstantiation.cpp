// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck


template<typename Ty>
struct normal_iterator {
  int FIELD;
};

void foo(normal_iterator<int>);
normal_iterator<int> baz();

void bar() {
  foo(baz());
}

void *bar2() {
  return (void*)foo;
}
