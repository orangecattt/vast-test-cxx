// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
// PR11930

typedef char vec_t __attribute__ ((__ext_vector_type__ (8)));
void h() {
// CHECK: store <8 x i8>
  vec_t v(0);
}
