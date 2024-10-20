// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s -DCC="__attribute__((vectorcall))" %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s -fms-compatibility -DWIN32 %target -o %t%output-suffix && %filecheck

#ifndef CC
#define CC
#endif

void usage() {
  auto lambda = [](int i, float f, double d) CC { return i + f + d; };

  double (*CC fp)(int, float, double) = lambda;
#ifdef WIN32
  double (*__attribute__((thiscall)) fp2)(int, float, double) = lambda;
  double (*__attribute__((stdcall)) fp3)(int, float, double) = lambda;
  double (*__attribute__((fastcall)) fp4)(int, float, double) = lambda;
  double (*__attribute__((vectorcall)) fp5)(int, float, double) = lambda;
#endif // WIN32
  fp(0, 1.1, 2.2);
#ifdef WIN32
  fp2(0, 1.1, 2.2);
  fp3(0, 1.1, 2.2);
  fp4(0, 1.1, 2.2);
  fp5(0, 1.1, 2.2);
#endif // WIN32

  auto x = +lambda;
}

