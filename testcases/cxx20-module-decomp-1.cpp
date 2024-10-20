// RUN: %driver -cc1 %isys -std=c++20 %s %target -o %t%output-suffix && %filecheck

export module Foo;

int ary[2];

export auto &[a, b] = ary;

namespace N {
export auto &[a, b] = ary;
auto &[c, d] = ary;
static auto &__attribute__((used))[e, f] = ary;
} // namespace N
