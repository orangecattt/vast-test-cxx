// RUN: %driver -cc1 %isys -std=c++23 %s %target -o %t%output-suffix && %filecheck

struct Functor {
  static int operator()(int x, int y) {
    return x + y;
  }
};

auto GetALambda() {
  return [](int x, int y) static {
    return x + y;
  };
}

void CallsTheLambda() {
  GetALambda()(1, 2);
}


Functor GetAFunctor() {
  return {};
}

void call_static_call_operator() {
  Functor f;
  f(101, 102);
  f.operator()(201, 202);
  Functor{}(301, 302);
  Functor::operator()(401, 402);
  GetAFunctor()(501, 502);
}


struct FunctorConsteval {
  consteval static int operator()(int x, int y) {
      return x + y;
  }
};

struct FunctorConstexpr {
  constexpr static int operator()(int x, int y) {
      return x + y;
  }
};

constexpr auto my_lambda = []() constexpr {
  return 3;
};

void test_consteval_constexpr() {
  int x = 0;
  int y = FunctorConstexpr{}(x, 2);
  constexpr int z1 = FunctorConsteval{}(2, 2);
  constexpr int z2 = FunctorConstexpr{}(2, 2);
  
  static_assert(z1 == 4);
  static_assert(z2 == 4);

  constexpr auto my_lambda = []() constexpr static {
      return 3;
  };
  constexpr int (*f)(void) = my_lambda;
  constexpr int k = f();
  static_assert(k == 3);
}

template <class T>
struct DepFunctor {
  static int operator()(T t) {
    return int(t);
  }
};

template<class T>
auto dep_lambda1() {
  return [](T t) static -> int {
    return t;
  };
}

auto dep_lambda2() {
  return [](auto t) static -> int {
    return t;
  };
}

void test_dep_functors() {
  int x = DepFunctor<float>{}(1.0f);
  int y = DepFunctor<bool>{}(true);

  int a = dep_lambda1<float>()(1.0f);
  int b = dep_lambda1<bool>()(true);

  int h = dep_lambda2()(1.0f);
  int i = dep_lambda2()(true);
}



struct __unique {
    static constexpr auto operator()() { return 4; };

    using P = int();
    constexpr operator P*() { return operator(); }
};

__unique four{};

int test_four() {
  return four();
}
