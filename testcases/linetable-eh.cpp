// RUN: %driver -cc1 %isys -gno-column-info -funwind-tables=2 -std=c++11 -fcxx-exceptions -fexceptions %s %target -o %t%output-suffix && %filecheck


typedef unsigned long long uint64_t;
template<class _Tp> class shared_ptr {
public:
  typedef _Tp element_type;
  element_type* __ptr_;
  ~shared_ptr();
  element_type* operator->() const noexcept {return __ptr_;}
};
class Context {
public:
    uint64_t GetIt();
};
class Foo
{
    bool bar();
    virtual shared_ptr<Context> GetContext () = 0;
};
# 253 "Foo.cpp" 3
bool
Foo::bar ()
{
  uint64_t current_address = GetContext()->GetIt();
  bool found_it = false;
# 267 "Foo.cpp" 3
  return found_it;
}
