// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

class Base {
public:
   virtual ~Base();
};

Base::~Base()
{
}

class Foo : public Base {
public:
   virtual ~Foo();
};

Foo::~Foo()
{
}
