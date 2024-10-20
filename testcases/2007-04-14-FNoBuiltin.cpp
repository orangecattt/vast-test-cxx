// RUN: %driver -cc1 %isys %s -fno-builtin %target -o %t%output-suffix && %filecheck
// Check that -fno-builtin is honored.

extern "C" int printf(const char*, ...);
void foo(const char *msg) {
  // CHECK: call{{.*}}printf
	printf("%s\n",msg);
}
