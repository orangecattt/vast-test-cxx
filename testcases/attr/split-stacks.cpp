// RUN: %driver -fsplit-stack -std=c++11 %s %target -S -o %t%output-suffix && %filecheck
// RUN: %driver -std=c++11 %s %target -S -o %t%output-suffix && %filecheck

int foo() {
  return 0;
}

template <typename T>
[[gnu::no_split_stack]]
int tnosplit() {
  return 0;
}

[[gnu::no_split_stack]]
int nosplit() {
  return tnosplit<int>();
}


