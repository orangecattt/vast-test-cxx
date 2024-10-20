// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct Base {

  void no_args_1(void (*callback)(void));
  __attribute__((callback(1))) void no_args_2(void (*callback1)(void), void (*callback2)(void));
  __attribute__((callback(callback1))) void no_args_3(void (*callback1)(void), void (*callback2)(void));

  __attribute__((callback(1))) virtual void
  virtual_1(void (*callback)(void));

  __attribute__((callback(callback, this, __, this))) virtual void
  this_unknown_this(void (*callback)(Base *, Base *, Base *));
};

__attribute__((callback(1))) void
Base::no_args_1(void (*callback)(void)) {
}

__attribute__((callback(2))) void Base::no_args_2(void (*callback1)(void), void (*callback2)(void)) {
}
__attribute__((callback(callback2))) void Base::no_args_3(void (*callback1)(void), void (*callback2)(void)) {
}

void Base::this_unknown_this(void (*callback)(Base *, Base *, Base *)) {
}

struct Derived_1 : public Base {
  __attribute__((callback(1))) virtual void
  virtual_1(void (*callback)(void)) override;
};

void Derived_1::virtual_1(void (*callback)(void)) {}

struct Derived_2 : public Base {
  void virtual_1(void (*callback)(void)) override;
};

void Derived_2::virtual_1(void (*callback)(void)) {}

