// RUN: %driver -cc1 %isys -fblocks %s -fexceptions -std=c++11 %target -o %t%output-suffix && %filecheck

auto unused = [](int i) { return i+1; };

auto used = [](int i) { return i+1; };
void *use = &used;

extern "C" auto cvar = []{};

int ARBSizeOf(int n) {
  typedef double(T)[8][n];
  using TT = double[8][n];
  return [&]() -> int {
    typedef double(T1)[8][n];
    using TT1 = double[8][n];
    return [&n]() -> int {
      typedef double(T2)[8][n];
      using TT2 = double[8][n];
      return sizeof(T) + sizeof(T1) + sizeof(T2) + sizeof(TT) + sizeof(TT1) + sizeof(TT2);
    }();
  }();
}


int a() { return []{ return 1; }(); }

int b(int x) { return [x]{return x;}(); }

int c(int x) { return [&x]{return x;}(); }

struct D { D(); D(const D&); int x; };
int d(int x) { D y[10]; return [x,y] { return y[x].x; }(); }


struct E { E(); E(const E&); ~E(); int x; };
int e(E a, E b, bool cond) { return [a,b,cond](){ return (cond ? a : b).x; }(); }


void f() {
  int (*fp)(int, int) = [](int x, int y){ return x + y; };
}

static int k;
int g() {
  int &r = k;
  return [] { return r; } ();
};

void staticarrayref(){
  static int array[] = {};
  (void)[](){
    int (&xxx)[0] = array;
    int y = xxx[0];
  }();
}

int PR22071_var;
int *PR22071_fun() {
  constexpr int &y = PR22071_var;
  return [&] { return &y; }();
}

namespace pr28595 {
  struct Temp {
    Temp();
    ~Temp() noexcept(false);
  };
  struct A {
    A();
    A(const A &a, const Temp &temp = Temp());
    ~A();
  };

  void after_init() noexcept;

  void test() {
    A array[3][5];

    after_init();

    (void) [array]{};
  }
}



struct A { ~A(); };
void h() {
  A (*h)() = [] { return A(); };
}

struct XXX {};
void nestedCapture () {
  XXX localKey;
  // ^() {
  //   [&]() {
  //     ^{ XXX k = localKey; };
  //   };
  // };
}

struct CaptureArrayAndThis {
  CaptureArrayAndThis() {
    char array[] = "floop";
    [array, this] {};
  }
} capture_array_and_this;

