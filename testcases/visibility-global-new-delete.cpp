// RUN: %driver -cc1 %isys %s -std=c++11 -fvisibility=hidden %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s -std=c++11 -fvisibility=default -fvisibility-global-new-delete=force-hidden %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s -std=c++11 -fvisibility=hidden -fvisibility-global-new-delete=force-protected %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s -std=c++11 -fvisibility=hidden -fvisibility-global-new-delete=force-default %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s -std=c++11 -fvisibility=hidden -fvisibility-global-new-delete=source %target -o %t%output-suffix && %filecheck

namespace std {
  typedef __typeof__(sizeof(0)) size_t;
  struct nothrow_t {};
}

// Definition which inherits visibility from the implicit compiler generated declaration.
void operator delete(void*) throw() {}
// CHECK: define [[LINKAGE]] void @_ZdlPv
