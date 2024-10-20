// RUN: %driver -cc1 %isys -std=c++17 -fchar8_t %s %target -o %t%output-suffix && %filecheck

// ITANIUM: define{{.*}} void @_Z1fDu(
// MSABI: define {{.*}}void @"?f@@YAX_Q@Z"(
void f(char8_t c) {}

// ITANIUM: define weak_odr void @_Z1gIiEvDTplplcvT__ELA4_KDuELDu114EE(
// MSABI: define weak_odr {{.*}}void @"??$g@H@@YAXPEB_Q@Z"(
template<typename T> void g(decltype(T() + u8"foo" + u8'r')) {}
template void g<int>(const char8_t*);
