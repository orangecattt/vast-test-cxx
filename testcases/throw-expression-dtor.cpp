// RUN: %driver -cc1 %isys %s -fcxx-exceptions -fexceptions %target -o %t%output-suffix && %filecheck
// expected-no-diagnostics
// PR7281

class A {
public:
    ~A();
};
class B : public A {
    void ice_throw();
};
void B::ice_throw() {
    throw *this;
}