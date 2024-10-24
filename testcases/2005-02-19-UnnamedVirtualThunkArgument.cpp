// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct Foo  {
    Foo();
    virtual ~Foo();
};

struct Bar  {
    Bar();
    virtual ~Bar();
    virtual bool test(bool) const;
};

struct Baz : public Foo, public Bar  {
    Baz();
    virtual ~Baz();
    virtual bool test(bool) const;
};

bool Baz::test(bool) const  {
    return true;
}
