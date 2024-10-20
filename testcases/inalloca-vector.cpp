// RUN: %driver -cc1 %isys -w %s %target -o %t%output-suffix && %filecheck


struct NonTrivial {
  NonTrivial();
  NonTrivial(const NonTrivial &o);
  unsigned handle;
};

typedef float __m128 __attribute__((__vector_size__(16), __aligned__(16)));
__m128 gv128;

void receive_vec_128(NonTrivial nt, __m128 x, __m128 y, __m128 z, __m128 w, __m128 q) {
  gv128 = x + y + z + w + q;
}

void pass_vec_128() {
  __m128 z = {0};
  receive_vec_128(NonTrivial(), z, z, z, z, z);
}




void __fastcall fastcall_receive_vec(__m128 x, __m128 y, __m128 z, __m128 w, int edx, __m128 q, NonTrivial nt) {
  gv128 = x + y + z + w + q;
}


void __vectorcall vectorcall_receive_vec(double xmm0, double xmm1, double xmm2,
                                         __m128 x, __m128 y, __m128 z,
                                         __m128 w, int edx, __m128 q, NonTrivial nt) {
  gv128 = x + y + z + w + q;
}
