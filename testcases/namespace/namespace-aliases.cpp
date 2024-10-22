// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
namespace A { }
namespace B = A;

namespace b {}

void foo() {
    namespace a = b;
}
