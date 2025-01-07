// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck


constexpr const char* str() {
  return "abc";
}

template<typename T>
struct Struct {
  T t1;
  T t2;
};

template<typename T, T V>
struct A {
  static constexpr const T SV[] = {V, V + 1};
  template <int I> __attribute__((annotate("test", V, str(), I))) void test() {}
  __attribute__((annotate("test", Struct<const T*>{&SV[0], &SV[1]}))) void test2() {}
};

void t() {
  A<unsigned, 9> a;
  a.test<8>();
  a.test2();
}

template<typename T, T V>
struct B {
template<typename T1, T1 V1>
struct foo {
  int v __attribute__((annotate("v_ann_0", str(), 90, V))) __attribute__((annotate("v_ann_1", V1)));
};
};

static B<int long, -1>::foo<unsigned, 9> gf;

int main(int argc, char **argv) {
    B<int, 7>::foo<unsigned, 9> f;
    f.v = argc;
    gf.v = argc;
    return 0;
}
