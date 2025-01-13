// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
template <typename T>
class A
{
    union { void *d; };

public:
    A() : d(0) { }
};

A<int> a0;
