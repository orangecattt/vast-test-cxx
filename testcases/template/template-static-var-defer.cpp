// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
class X {
  template <class Dummy> struct COMTypeInfo {
    static const int kIID;
  };
  static const int& GetIID() {return COMTypeInfo<int>::kIID;}
};
template <class Dummy> const int X::COMTypeInfo<Dummy>::kIID = 10;



