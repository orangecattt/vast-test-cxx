// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

// Builtins inside a namespace inside an extern "C" must be considered builtins.
extern "C" {
namespace X {
double __builtin_fabs(double);
float __builtin_fabsf(float) noexcept;
} // namespace X
}

int o = X::__builtin_fabs(-2.0);
// CHECK: @o ={{.*}} global i32 2, align 4

long p = X::__builtin_fabsf(-3.0f);
// CHECK: @p ={{.*}} global i64 3, align 8

// PR8839
extern "C" char memmove();

int main() {
  // CHECK: call {{signext i8|i8}} @memmove()
  return memmove();
}

struct S;
// CHECK: define {{.*}} @_Z9addressofbR1SS0_(
S *addressof(bool b, S &s, S &t) {
  // CHECK: %[[LVALUE:.*]] = phi
  // CHECK: ret ptr %[[LVALUE]]
  return __builtin_addressof(b ? s : t);
}

namespace std { template<typename T> T *addressof(T &); }

// CHECK: define {{.*}} @_Z13std_addressofbR1SS0_(
S *std_addressof(bool b, S &s, S &t) {
  // CHECK: %[[LVALUE:.*]] = phi
  // CHECK: ret ptr %[[LVALUE]]
  return std::addressof(b ? s : t);
}

namespace std { template<typename T> T *__addressof(T &); }

// CHECK: define {{.*}} @_Z15std___addressofbR1SS0_(
S *std___addressof(bool b, S &s, S &t) {
  // CHECK: %[[LVALUE:.*]] = phi
  // CHECK: ret ptr %[[LVALUE]]
  return std::__addressof(b ? s : t);
}

extern "C" int __builtin_abs(int); // #1
long __builtin_abs(long);          // #2
extern "C" int __builtin_abs(int); // #3

int x = __builtin_abs(-2);
// CHECK:      [[X:%.+]] = call i32 @llvm.abs.i32(i32 -2, i1 true)
// CHECK-NEXT: store i32 [[X]], ptr @x, align 4

long y = __builtin_abs(-2l);
// CHECK:  [[Y:%.+]] = call noundef i64 @_Z13__builtin_absl(i64 noundef -2)
// CHECK:  store i64 [[Y]], ptr @y, align 8

extern const char char_memchr_arg[32];
char *memchr_result = __builtin_char_memchr(char_memchr_arg, 123, 32);
// CHECK: call ptr @memchr(ptr noundef @char_memchr_arg, i32 noundef 123, i64 noundef 32)

int constexpr_overflow_result() {
  constexpr int x = 1;
  // CHECK: alloca i32
  constexpr int y = 2;
  // CHECK: alloca i32
  int z;
  // CHECK: [[Z:%.+]] = alloca i32

  __builtin_sadd_overflow(x, y, &z);
  return z;
  // CHECK: [[RET_PTR:%.+]] = extractvalue { i32, i1 } %0, 0
  // CHECK: store i32 [[RET_PTR]], ptr [[Z]]
  // CHECK: [[RET_VAL:%.+]] = load i32, ptr [[Z]]
  // CHECK: ret i32 [[RET_VAL]]
}
