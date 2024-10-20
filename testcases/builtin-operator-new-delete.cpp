// RUN: %driver -cc1 %isys %s -faligned-allocation -fsized-deallocation %target -o %t%output-suffix && %filecheck

typedef __SIZE_TYPE__ size_t;

template<typename T> void *operator new(size_t, int (*)(T));

void *operator new(size_t);

namespace std {
  struct nothrow_t {};
  enum class align_val_t : size_t { __zero = 0,
                                  __max = (size_t)-1 };
}
std::nothrow_t nothrow;

void *operator new(size_t, void*) throw();
void operator delete(void*, void*) throw();
void *operator new[](size_t, void*) throw();
void operator delete[](void*, void*) throw();

void *operator new(size_t, const std::nothrow_t &) throw();
void *operator new[](size_t, const std::nothrow_t &) throw();
void operator delete(void *, const std::nothrow_t &) throw();
void operator delete[](void *, const std::nothrow_t &) throw();

void *operator new(size_t, void*, bool) throw();
void *operator new[](size_t, void*, bool) throw();


extern "C" void test_basic() {
  __builtin_operator_delete(__builtin_operator_new(4));
}

extern "C" void test_aligned_alloc() {
  __builtin_operator_delete(__builtin_operator_new(4, std::align_val_t(4)), std::align_val_t(4));
}

extern "C" void test_sized_delete() {
  __builtin_operator_delete(__builtin_operator_new(4), 4);
}



