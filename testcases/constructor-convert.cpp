// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

class Twine {
public:
  Twine(const char *Str) { }
};

static void error(const Twine &Message) {}

template<typename>
struct opt_storage {
  void f() {
    error("cl::location(x) specified more than once!");
  }
};

void f(opt_storage<int> o) {
  o.f();
}
