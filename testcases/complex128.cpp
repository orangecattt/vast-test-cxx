// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

// Define __complex128 type corresponding to __float128 (as in GCC headers).
typedef _Complex float __attribute__((mode(TC))) __complex128;

void check() {
  // CHECK: alloca { fp128, fp128 }
  __complex128 tmp;
}
