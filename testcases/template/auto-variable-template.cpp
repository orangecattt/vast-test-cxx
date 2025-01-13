// RUN: %driver -cc1 %isys -std=c++14 %s %target -o %t%output-suffix && %filecheck

struct f {
  void operator()() const {}
};

template <typename T> auto vtemplate = f{};

int main() { vtemplate<int>(); }



template <typename>
struct pack {
  template <typename T>
  constexpr static auto some_boolean_cx_value = true;
};

auto usage() {
  return pack<char>::some_boolean_cx_value<int>;
}


auto otherusage() {
  return pack<char>{}.some_boolean_cx_value<int>;
}

