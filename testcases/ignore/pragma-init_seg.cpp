// RUN: %driver -cc1 %isys %s -fms-extensions %target -o %t%output-suffix && %filecheck

int f();


namespace simple_init {
#pragma init_seg(compiler)
int x = f();

#pragma init_seg(lib)
int y = f();

#pragma init_seg(user)
int z = f();
}

#pragma init_seg(".asdf")

namespace internal_init {
namespace {
int x = f();
}
}

namespace selectany_init {
int __declspec(selectany) x = f();
}

namespace explicit_template_instantiation {
template <typename T> struct A { static const int x; };
template <typename T> const int A<T>::x = f();
template struct A<int>;
}

namespace implicit_template_instantiation {
template <typename T> struct A { static const int x; };
template <typename T> const int A<T>::x = f();
int g() { return A<int>::x; }
}


