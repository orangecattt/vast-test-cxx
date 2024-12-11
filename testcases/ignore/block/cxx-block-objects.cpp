// RUN: %driver -cc1 %isys %s -fblocks %target -o %t%output-suffix && %filecheck

extern "C" {
extern "C" void *_Block_copy(const void *aBlock);
extern "C" void _Block_release(const void *aBlock);
}

class A {
public:
        int x;
        A(const A &o);
        A();
        virtual ~A();
        void hello() const;
};

int
main()
{
        A a;
        void (^c)(void) = ((__typeof(^{ a.hello(); }))_Block_copy((const void *)(^{ a.hello(); })));
        c();
        _Block_release((const void *)(c));
        return 0;
}



