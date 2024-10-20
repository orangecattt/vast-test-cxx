// RUN: %driver -cc1 %isys -std=c++11 -fms-extensions %s %target -o %t%output-suffix && %filecheck


#pragma code_seg(push, "something")

template <typename T>
struct __declspec(code_seg("foo_one")) ClassOne {
  int bar1(T t) { return int(t); }
  int bar2(T t);
  int bar3(T t);
};

template <typename T>
int ClassOne<T>::bar2(T t) {
  return int(t);
}

int caller1() {
  ClassOne<int> coi;
  return coi.bar1(6) + coi.bar2(3);
}



template <typename T>
struct ClassTwo {
  int bar11(T t) { return int(t); }
  int bar22(T t);
  int bar33(T t);
};

#pragma code_seg("newone")

template <typename T>
int ClassTwo<T>::bar22(T t) {
  return int(t);
}

#pragma code_seg("someother")

template <typename T>
int ClassTwo<T>::bar33(T t) {
  return int(t);
}

#pragma code_seg("yetanother")

int caller2() {
  ClassTwo<int> coi;
  return coi.bar11(6) + coi.bar22(3) + coi.bar33(44);
}


template<>
struct ClassOne<double>
{
  int bar44(double d) { return 1; }
};
template<>
struct  __declspec(code_seg("foo_three")) ClassOne<long>
{
  int bar55(long d) { return 1; }
};

#pragma code_seg("onemore")
int caller3() {
  ClassOne<double> d;
  ClassOne<long> l;
  return d.bar44(1.0)+l.bar55(1);
}



template <typename T>
int __declspec(code_seg("foo_four")) bar66(T t) { return int(t); }

template<>
int bar66(int i) { return 0; }

#pragma code_seg(pop)

template<>
int bar66(char c) { return 0; }

struct A1 {int i;};
template<>
int __declspec(code_seg("foo_five")) bar66(A1 a) { return a.i; }

int caller4()
{
return bar66(0) + bar66(1.0) + bar66('c');
}



