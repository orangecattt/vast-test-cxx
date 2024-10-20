// RUN: %driver -cc1 %isys -std=c++20 %s %target -o %t%output-suffix && %filecheck

export module FOO;

class One;
class Two;

export template<typename T> struct TPL
{
void M (T *);
template<typename U> void N (T *, U*);
};

template<typename T>
void TPL<T>::M (T *) {}

template<typename T> template<typename U> void TPL<T>::N (T *, U*) {}

template void TPL<One>::M (One *);
template void TPL<One>::N<Two> (One *, Two *);

namespace NMS {
class One;
class Two;

export template<typename T> struct TPL
{
void M (T *);
template<typename U> void N (T *, U*);
};

template<typename T>
void TPL<T>::M (T *) {}

template<typename T> template<typename U> void TPL<T>::N (T *, U*) {}

template void TPL<One>::M (One *);
template void TPL<One>::N<Two> (One *, Two *);
}
