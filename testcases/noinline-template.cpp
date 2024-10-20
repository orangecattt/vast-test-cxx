// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck



template <class Ty> struct Vector  {
  void growStorageBy();
};
template <class T> __attribute__((noinline)) void Vector<T>::growStorageBy() {
}
void foo() {
 Vector<int> strs;
 strs.growStorageBy();
}

