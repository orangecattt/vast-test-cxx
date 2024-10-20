// RUN: %driver -cc1 %isys -fexceptions -fcxx-exceptions %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -fexceptions -exception-model=dwarf -fcxx-exceptions %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -fexceptions -exception-model=seh -fcxx-exceptions %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -fexceptions -exception-model=sjlj -fcxx-exceptions %s %target -o %t%output-suffix && %filecheck





extern void g();





void f() {
  try {
    g();
  } catch (...) {
  }
}

#if defined(__SEH_EXCEPTIONS__)

void h(void) {
  __try {
    g();
  } __finally {
  }
}
#endif

