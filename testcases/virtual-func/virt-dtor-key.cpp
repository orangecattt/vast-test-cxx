// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
class foo {
   foo();
   virtual ~foo();
};

foo::~foo() {
}
