// RUN: %driver -cc1 %isys -std=c++20 %s %target -o %t%output-suffix && %filecheck

namespace Issue57960 {
template<auto>
class F {};

template<typename D>
F<[]{}> E() {
    return {};
}

static auto f = E<int>();
}
