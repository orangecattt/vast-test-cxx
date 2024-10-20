// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

int defn  [[clang::loader_uninitialized]];

static int defn_static [[clang::loader_uninitialized]] __attribute__((used));

int* func(void)
{
  static int data [[clang::loader_uninitialized]];
  return &data;
}

class trivial
{
  float x;
};

trivial ut [[clang::loader_uninitialized]];

double arr[32] __attribute__((loader_uninitialized));

double arr2 [[clang::loader_uninitialized]] [4];

template<typename T> struct templ{T * t;};

templ<int> templ_int [[clang::loader_uninitialized]];

templ<trivial> templ_trivial [[clang::loader_uninitialized]];

struct incomplete;
templ<incomplete> templ_incomplete [[clang::loader_uninitialized]];
