// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck


template<typename T> struct TLS { static thread_local T *mData; };
inline decltype(nullptr) non_constant_initializer() { return nullptr; }
template<typename T> thread_local T *TLS<T>::mData = non_constant_initializer();
struct S {};
S *current() { return TLS<S>::mData; };




