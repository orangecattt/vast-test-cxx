// RUN: %driver -cc1 %isys -std=c++17 %s %target -o %t%output-suffix && %filecheck

void doSomething();

struct A {
  A() {};
  ~A() noexcept {
    doSomething();
  }

  A & operator=(A a) & noexcept {
    return *this;
  }
};

template<typename T>
struct B {
  void test() {a = {};}
  // CHECK: define linkonce_odr void @_ZN1BIiE4testEv
  // CHECK: call void @_ZN1AC1Ev(ptr noundef nonnull align 1 dereferenceable(1)
  // CHECK: [[CALL:%.*]] = call noundef nonnull align 1 dereferenceable(1) ptr @_ZNR1AaSES_
  // CHECK: call void @_ZN1AD2Ev(ptr noundef nonnull align 1 dereferenceable(1)

  A a;
};

void client(B<int> &f) {f.test();}
