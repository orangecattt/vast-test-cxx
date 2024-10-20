// RUN: %driver -cc1 %isys < %s -fms-extensions -x c++ %target -o %t%output-suffix && %filecheck



struct A {
  __attribute__((optnone))
  static int static_optnone_method(int a) {
    return a + a;
  }

  __attribute__((optnone))
  int optnone_method(int a) {
    return a + a + a + a;
  }

  __attribute__((optnone))
  int optnone_decl_method(int a);

  __forceinline static int static_forceinline_method(int a);
  __attribute__((always_inline)) int alwaysinline_method(int a);
  __attribute__((noinline)) int noinline_method(int a);
  __attribute__((minsize)) int minsize_method(int a);
};

void foo() {
  A a;
  A::static_optnone_method(4);
  a.optnone_method(14);
  a.optnone_decl_method(12);
  A::static_forceinline_method(5);
  a.alwaysinline_method(5);
  a.noinline_method(6);
  a.minsize_method(7);
}

int A::optnone_decl_method(int a) {
  return a;
}

__attribute__((optnone))
int A::static_forceinline_method(int a) {
  return a + a + a + a;
}

__attribute__((optnone))
int A::alwaysinline_method(int a) {
  return a + a + a + a;
}

__attribute__((optnone))
int A::noinline_method(int a) {
  return a + a + a + a;
}

__attribute__((optnone))
int A::minsize_method(int a) {
  return a + a + a + a;
}




struct B {
  virtual int pure_virtual(int a) = 0;
  __attribute__((optnone))
  virtual int pure_virtual_with_optnone(int a) = 0;

  virtual int base(int a) {
    return a + a + a + a;
  }

  __attribute__((optnone))
  virtual int optnone_base(int a) {
    return a + a + a + a;
  }

  __attribute__((optnone))
  virtual int only_base_virtual(int a) {
    return a + a;
  }
};

struct C : public B {
  __attribute__((optnone))
  virtual int pure_virtual(int a) {
    return a + a + a + a;
  }

  virtual int pure_virtual_with_optnone(int a) {
    return a + a + a + a;
  }

  __attribute__((optnone))
  virtual int base(int a) {
    return a + a;
  }

  virtual int optnone_base(int a) {
    return a + a;
  }

  int only_base_virtual(int a) {
    return a + a + a + a;
  }
};

int bar() {
  C c;
  int result;
  result = c.pure_virtual(3);
  result += c.pure_virtual_with_optnone(2);
  result += c.base(5);
  result += c.optnone_base(7);
  result += c.only_base_virtual(9);
  return result;
}



