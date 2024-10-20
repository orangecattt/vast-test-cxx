// RUN: %driver -cc1 %isys %s -std=c++11 %target -o %t%output-suffix && %filecheck






namespace test0 {
  struct  basic_streambuf   {
    virtual       ~basic_streambuf();
  };
  template<typename _CharT >
  struct stdio_sync_filebuf : public basic_streambuf {
    virtual void      xsgetn();
  };

  template<> void stdio_sync_filebuf<int[1]>::xsgetn()  {
  }
  template<> void stdio_sync_filebuf<int[2]>::xsgetn()  {
  }
  template<> void stdio_sync_filebuf<int[3]>::xsgetn()  {
  }
  template<> void stdio_sync_filebuf<int[4]>::xsgetn()  {
  }
  extern template class stdio_sync_filebuf<int[2]>;

  template class stdio_sync_filebuf<int[3]>;
  stdio_sync_filebuf<int[4]> implicit_instantiation;
}

namespace test1 {
  struct  basic_streambuf   {
    virtual       ~basic_streambuf();
  };
  template<typename _CharT >
  struct stdio_sync_filebuf : public basic_streambuf {
    virtual void      xsgetn();
  };

  template<> void stdio_sync_filebuf<wchar_t>::xsgetn();
}

namespace test2 {
  template<typename T1>
  class C {
  public:
    virtual ~C();
    void zedbar(double) {
    }
    template<typename T2>
    void foobar(T2 foo) {
    }
  };
  extern template class C<int>;
  void g() {
    C<int> a;

    a.foobar(0.0);

    a.zedbar(0.0);
  }
}

namespace test3 {
  template<typename T>
  class basic_fstreamXX  {
    virtual void foo(){}
    virtual void is_open() const  { }
  };

  extern template class basic_fstreamXX<char>;
  template void basic_fstreamXX<char>::is_open() const;
}

namespace test3 {
  template <typename T>
  struct S  {
      virtual void m();
  };
  
  template<typename T>
  void S<T>::m() { }

  template void S<int>::m();
}

namespace test4 {
  template <class T> struct A { static void foo(); };

  class B {
    template <class T> friend void A<T>::foo();
    B();
  };

  template <class T> void A<T>::foo() {
    B b;
  }

  unsigned test() {
    A<int>::foo();
  }
}

namespace PR8505 {
template <int i> class A {
  class B* g;
};
class B {
  void f () {}
};
template class A<0>;
}

namespace PR10001 {
  template <typename T> struct S {
    static const int arr[];
    static const int arr2[];
    static const int x, y;
    static int f();
  };

  extern int foo();
  extern int kBar;

  template <typename T> const int S<T>::arr[] = { 1, 2, foo() }; // possible side effects
  template <typename T> const int S<T>::arr2[] = { 1, 2, kBar }; // no side effects
  template <typename T> const int S<T>::x = sizeof(arr) / sizeof(arr[0]);
  template <typename T> const int S<T>::y = sizeof(arr2) / sizeof(arr2[0]);
  template <typename T> int S<T>::f() { return x + y; }

  int x = S<int>::f();
}

namespace PR10666 {
  template <int N> struct S {
    void f1() { S<1> s; }
    friend void g1(S s) {}
    friend void h1(S s);
    void f2() { S<2> s; }
    friend void g2(S s) {}
    friend void h2(S s);
    void f3() { S<3> s; }
  };
  void test(S<1> s1, S<2> s2, S<3> s3) {
    g1(s1); g1(s2); g1(s3);
    g2(s1); g2(s2); g2(s3);
    h1(s1); h1(s2); h1(s3);
    h2(s1); h2(s2); h2(s3);
  }
}
