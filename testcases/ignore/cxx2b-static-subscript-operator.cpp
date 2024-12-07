// RUN: %driver -cc1 %isys -std=c++23 %s %target -o %t%output-suffix && %filecheck

struct Functor {
  static int operator[](int x, int y) {
    return x + y;
  }
};

Functor GetAFunctor() {
  return {};
}

void call_static_subscript_operator() {
  Functor f;
  f[101, 102];
  f.operator[](201, 202);
  Functor{}[301, 302];
  Functor::operator[](401, 402);
  GetAFunctor()[501, 502];
}


struct FunctorConsteval {
  consteval static int operator[](int x, int y) {
      return x + y;
  }
};

struct FunctorConstexpr {
  constexpr static int operator[](int x, int y) {
      return x + y;
  }
};

void test_consteval_constexpr() {
  int x = 0;
  int y = FunctorConstexpr{}[x, 2];
  constexpr int z1 = FunctorConsteval{}[2, 2];
  constexpr int z2 = FunctorConstexpr{}[2, 2];
  
  static_assert(z1 == 4);
  static_assert(z2 == 4);
}

template <class T>
struct DepFunctor {
  static int operator[](T t) {
    return int(t);
  }
};

void test_dep_functors() {
  int x = DepFunctor<float>{}[1.0f];
  int y = DepFunctor<bool>{}[true];
}

