// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck


#define EXCLUDE_FROM_EXPLICIT_INSTANTIATION __attribute__((exclude_from_explicit_instantiation))

template <class T>
struct Foo {
  EXCLUDE_FROM_EXPLICIT_INSTANTIATION        inline void non_static_member_function1();
  EXCLUDE_FROM_EXPLICIT_INSTANTIATION               void non_static_member_function2();

  EXCLUDE_FROM_EXPLICIT_INSTANTIATION static inline void static_member_function1();
  EXCLUDE_FROM_EXPLICIT_INSTANTIATION static        void static_member_function2();

  EXCLUDE_FROM_EXPLICIT_INSTANTIATION static        int static_data_member;

  struct EXCLUDE_FROM_EXPLICIT_INSTANTIATION member_class1 {
    static void static_member_function() { }
  };

  struct member_class2 {
    EXCLUDE_FROM_EXPLICIT_INSTANTIATION static void static_member_function() { }
  };
};

template <class T> inline void Foo<T>::non_static_member_function1() { }
template <class T>        void Foo<T>::non_static_member_function2() { }

template <class T> inline void Foo<T>::static_member_function1() { }
template <class T>        void Foo<T>::static_member_function2() { }

template <class T>        int Foo<T>::static_data_member = 0;

extern template struct Foo<int>;

void use() {
  Foo<int> f;

  f.non_static_member_function1();

  f.non_static_member_function2();

  Foo<int>::static_member_function1();

  Foo<int>::static_member_function2();

  int& odr_use = Foo<int>::static_data_member;

  Foo<int>::member_class1::static_member_function();

  Foo<int>::member_class2::static_member_function();
}
