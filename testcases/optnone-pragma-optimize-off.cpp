// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck


_Pragma("clang optimize off")

void foo(int p) {
  auto lambda = [&p]() { ++p; };
  lambda();
}

_Pragma("clang optimize on")

