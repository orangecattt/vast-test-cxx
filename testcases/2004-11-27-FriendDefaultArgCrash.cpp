// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

// PR447

namespace nm {
  struct str {
    friend void foo(int arg = 0) {};
  };
}
