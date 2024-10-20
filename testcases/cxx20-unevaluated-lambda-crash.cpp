// RUN: %driver -cc1 %isys -std=c++20 %s %target -o %t%output-suffix && %filecheck

// CHECK-LABEL: define linkonce_odr void @"_ZN10Issue579601EIiEENS_1FILNS_3$_0EEEEv"()
namespace Issue57960 {
template<auto>
class F {};

template<typename D>
F<[]{}> E() {
    return {};
}

static auto f = E<int>();
}
