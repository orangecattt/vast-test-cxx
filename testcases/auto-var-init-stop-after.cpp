// RUN: %driver -cc1 %isys -ftrivial-auto-var-init=pattern -ftrivial-auto-var-init-stop-after=1 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -ftrivial-auto-var-init=pattern -ftrivial-auto-var-init-stop-after=2 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -ftrivial-auto-var-init=pattern -ftrivial-auto-var-init-stop-after=3 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -ftrivial-auto-var-init=pattern -ftrivial-auto-var-init-stop-after=4 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -ftrivial-auto-var-init=pattern -ftrivial-auto-var-init-stop-after=5 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -ftrivial-auto-var-init=zero -ftrivial-auto-var-init-stop-after=1 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -ftrivial-auto-var-init=zero -ftrivial-auto-var-init-stop-after=2 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -ftrivial-auto-var-init=zero -ftrivial-auto-var-init-stop-after=3 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -ftrivial-auto-var-init=zero -ftrivial-auto-var-init-stop-after=4 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -ftrivial-auto-var-init=zero -ftrivial-auto-var-init-stop-after=5 %s %target -o %t%output-suffix && %filecheck

#define ARRLEN 10

typedef struct {
  int i;
  char c;
} S;

int foo(unsigned n) {
  long a = 888;
  S arr[ARRLEN];
  S vla[n];
  void *p;
  p = __builtin_alloca(sizeof(unsigned long long) * n);

  return 0;
}
