// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

#pragma pack(4)

struct Bork {
  unsigned int f1 : 3;
  unsigned int f2 : 30;
};

int Foo(Bork *hdr) {
  hdr->f1 = 7;
  hdr->f2 = 927;
}
