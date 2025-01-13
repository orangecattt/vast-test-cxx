// RUN: %driver -cc1 %isys -std=c++14 %s %target -o %t%output-suffix && %filecheck

template<int N> int Fib = Fib<N-2> + Fib<N-1>;
template<> int Fib<0> = 0;
template<> int Fib<1> = 1;
int f = Fib<5>;

template<int N> int Fib2 = Fib2<N-1> + Fib2<N-2>;
template<> int Fib2<0> = 0;
template<> int Fib2<1> = 1;
int f2 = Fib2<5>;

