// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct FOO {
	unsigned int x;
};

#pragma pack(push, 2)

// CHECK: %struct.BAR = type <{ %struct.FOO, i8, i8 }>
struct BAR : FOO {
	char y;
};

#pragma pack(pop)

BAR f(BAR x) {
  return x;
}
