// RUN: %driver -cc1 %isys -std=c++14 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++17 %s %target -o %t%output-suffix && %filecheck

namespace std {
  template<typename T> class initializer_list {
    const T *data;
    __SIZE_TYPE__ size;

  public:
    initializer_list();
  };
}

namespace ParenBraceInitList {
  struct Vector {
    Vector(std::initializer_list<int>);
    ~Vector();
  };

  struct Base { Base(Vector) {} };

  template<int> void f() {
    Base({0});
  }
  template void f<0>();
}
