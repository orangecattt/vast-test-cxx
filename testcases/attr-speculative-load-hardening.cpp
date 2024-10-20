// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

// RUN: %driver -cc1 %isys -mspeculative-load-hardening -std=c++11 %s %target -o %t%output-suffix && %filecheck


// RUN: %driver -mno-speculative-load-hardening -std=c++11 %s %target -S -o %t%output-suffix && %filecheck


[[clang::speculative_load_hardening]]
int test1() {
  return 42;
}

int __attribute__((speculative_load_hardening)) test2() {
  return 42;
}

[[clang::no_speculative_load_hardening]]
int test3() {
  return 42;
}

int __attribute__((no_speculative_load_hardening)) test4() {
  return 42;
}





