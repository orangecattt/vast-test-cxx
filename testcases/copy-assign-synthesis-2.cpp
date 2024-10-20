// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
struct A {};
A& (A::*x)(const A&) = &A::operator=;
// CHECK-LABEL: define linkonce_odr {{.*}}ptr @_ZN1AaSERKS_
