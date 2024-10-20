// RUN: %driver -cc1 %isys %s -std=c++11 %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s -std=c++11 -fvisibility=hidden %target -o %t%output-suffix && %filecheck

#define HIDDEN __attribute__((visibility("hidden")))
#define PROTECTED __attribute__((visibility("protected")))
#define DEFAULT __attribute__((visibility("default")))
#define TYPE_HIDDEN __attribute__((type_visibility("hidden")))
#define TYPE_PROTECTED __attribute__((type_visibility("protected")))
#define TYPE_DEFAULT __attribute__((type_visibility("default")))

#if !__has_attribute(type_visibility)
#error No type_visibility attribute!
#endif

namespace temp0 {
  struct A;
  template <class T> struct TYPE_DEFAULT B {
    virtual void foo() {}
  };

  template struct B<A>;
}

namespace temp1 {
  struct TYPE_DEFAULT A;
  template <class T> struct TYPE_DEFAULT B {
    virtual void foo() {}
  };

  template struct B<A>;
}

namespace temp2 {
  struct TYPE_DEFAULT A;
  template <class T> struct B {
    virtual void foo() {}
  };

  template struct B<A>;
}

namespace temp3 {
  struct TYPE_HIDDEN A;
  template <class T> struct TYPE_DEFAULT B {
    virtual void foo() {}
  };

  template struct B<A>;
}

namespace temp4 {
  struct TYPE_DEFAULT A;
  template <class T> struct TYPE_HIDDEN B {
    virtual void foo() {}
  };

  template struct B<A>;
}

namespace type0 {
  struct TYPE_DEFAULT A {
    virtual void foo();
  };

  void A::foo() {}
}

namespace type1 {
  struct HIDDEN TYPE_DEFAULT A {
    virtual void foo();
  };

  void A::foo() {}
}

namespace type2 {
  struct TYPE_HIDDEN A {
    virtual void foo();
  };

  void A::foo() {}
}

namespace type3 {
  struct DEFAULT TYPE_HIDDEN A {
    virtual void foo();
  };

  void A::foo() {}
}

