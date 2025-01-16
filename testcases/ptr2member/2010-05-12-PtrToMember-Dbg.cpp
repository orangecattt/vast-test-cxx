// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
class Foo
{
 public:
  int x;
  int y;
  Foo (int i, int j) { x = i; y = j; }
};


Foo foo(10, 11);

int main() {
  int Foo::* pmi = &Foo::y;
  return foo.*pmi;
}
