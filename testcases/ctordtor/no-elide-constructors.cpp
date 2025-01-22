// RUN: %driver -cc1 %isys -std=c++98 -fno-elide-constructors %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++11 -fno-elide-constructors %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++98 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

class X {
public:
  X();
  X(const X&);
#if __cplusplus >= 201103L
  X(X&&);
#endif
  ~X();
};

X Test()
{
  X x;


  return x;
}
