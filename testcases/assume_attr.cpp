// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -x c++ -emit-pch %s -o %t
// RUN: %driver -cc1 %isys -include-pch %t %s %target -o %t%output-suffix && %filecheck

#ifndef HEADER
#define HEADER


__attribute__((assume("foo:before1"))) void foo();

__attribute__((assume("foo:before2")))
__attribute__((assume("foo:before3"))) void
foo();


__attribute__((assume("baz:before1"))) static void baz();

__attribute__((assume("baz:before2")))
__attribute__((assume("baz:before3"))) static void
baz();

__attribute__((assume("baz:def1,baz:def2"))) static void baz() { foo(); }

__attribute__((assume("baz:after"))) static void baz();


__attribute__((assume("bar:before1"))) void bar();

__attribute__((assume("bar:before2")))
__attribute__((assume("bar:before3"))) void
bar();

__attribute__((assume("bar:def1,bar:def2"))) void bar() { baz(); }

__attribute__((assume("bar:after"))) void bar();


__attribute__((assume("foo:after"))) void foo();

class C {
  __attribute__((assume("C:private_method"))) void private_method();
  __attribute__((assume("C:private_static"))) static void private_static();

public:
  __attribute__((assume("C:public_method1"))) void public_method();
  __attribute__((assume("C:public_static1"))) static void public_static();
};

__attribute__((assume("C:public_method2"))) void C::public_method() {
  private_method();
}

__attribute__((assume("C:public_static2"))) void C::public_static() {
  private_static();
}

template <typename T>
__attribute__((assume("template_func<T>"))) void template_func() {}

template <>
__attribute__((assume("template_func<float>"))) void template_func<float>() {}

template <>
void template_func<int>() {}

template <typename T>
struct S {
  __attribute__((assume("S<T>::method"))) void method();
};

template <>
__attribute__((assume("S<float>::method"))) void S<float>::method() {}

template <>
void S<int>::method() {}


#endif
