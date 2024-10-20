// RUN: %driver -cc1 %isys %s -fms-extensions -stack-protector 2 %target -o %t%output-suffix && %filecheck

#pragma strict_gs_check(on)

extern "C" void test0() {
}
// CHECK: define {{.*}} @test0() #[[ATTR_TEST0:[0-9]*]] {


// CHECK: attributes #[[ATTR_TEST0]] = {{.*}} sspstrong

