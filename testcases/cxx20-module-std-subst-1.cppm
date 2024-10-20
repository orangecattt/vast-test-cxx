// RUN: %driver -cc1 %isys -std=c++20 %s %target -o %t%output-suffix && %filecheck

module;
# 5 __FILE__ 1
class Pooh;
class Piglet;
# 8 "" 2

# 8 "" 1 3
export module std; // might happen, you can't say it won't!
# 9 "" 2 3

namespace std {
export template<typename T> class allocator {
void M (T *);
template <typename U> U *N (T *);
};

template<typename T> void allocator<T>::M (T *) {}
template<typename T> template<typename U> U *allocator<T>::N (T *) {
return nullptr;
}

template void allocator<int>::M (int *);
template float *allocator<int>::N<float> (int *);
}

template void std::allocator<Pooh>::M (Pooh *);
template Piglet *std::allocator<Pooh>::N<Piglet> (Pooh *);
