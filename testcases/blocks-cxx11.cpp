// RUN: %driver -cc1 %isys %s -fblocks -std=c++11 %target -o %t%output-suffix && %filecheck

template <class T> void takeItByValue(T);
void takeABlock(void (^)());

namespace test_int {
  void test() {
    const int x = 100;
    takeABlock(^{ takeItByValue(x); });
  }
}

namespace test_int_ref {
  void test() {
    const int y = 200;
    const int &x = y;
    takeABlock(^{ takeItByValue(x); });

  }
}

namespace test_float {
  void test() {
    const float x = 1;
    takeABlock(^{ takeItByValue(x); });
  }
}

namespace test_float_ref {
  void test() {
    const float y = 100;
    const float &x = y;
    takeABlock(^{ takeItByValue(x); });

  }
}

namespace test_complex_int {
  void test() {
    constexpr _Complex int x = 500;
    takeABlock(^{ takeItByValue(x); });

  }
}

namespace test_complex_int_ref {
  void test() {
    const _Complex int y = 100;
    const _Complex int &x = y;
    takeABlock(^{ takeItByValue(x); });
  }
}

namespace test_complex_int_ref_mutable {
  _Complex int y = 100;
  void test() {
    const _Complex int &x = y;
    takeABlock(^{ takeItByValue(x); });
  }
}

namespace test_block_in_lambda {
  void takeBlock(void (^block)());

  struct A {
    void *p;
    A(const A &);
    ~A();
    void use() const;
  };

  void test(A a) {
    auto lambda = [a]() {
      takeBlock(^{ a.use(); });
    };
    lambda(); // make sure we emit the invocation function
  }
}
