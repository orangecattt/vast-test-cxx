// RUN: %driver -cc1 %isys -std=c++1z %s -w %target -o %t%output-suffix && %filecheck

typedef int T;
void f() {
  if (int a = 5; a < 8)
    ;
}

void f1() {
  if (int a, b = 5; int c = 7)
    ;
}

int f2() {
  if (T{f2()}; int c = 7)
    ;
  return 2;
}

void g() {
  switch (int a = 5; a) {
    case 0:
      break;
  }
}

void g1() {
  switch (int a, b = 5; int c = 7) {
    case 0:
      break;
  }
}

int g2() {
  switch (T{f2()}; int c = 7) {
    case 0:
      break;
  }
  return 2;
}
