// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

// Test the attributes for the lambda function contains 'optnone' as result of
// the _Pragma("clang optimize off").

_Pragma("clang optimize off")

void foo(int p) {
  auto lambda = [&p]() { ++p; };
  lambda();
  // CHECK: define {{.*}} @"_ZZ3fooiENK3$_0clEv"({{.*}}) #[[LAMBDA_ATR:[0-9]+]]
}

_Pragma("clang optimize on")

// CHECK: attributes #[[LAMBDA_ATR]] = { {{.*}} optnone {{.*}} }
