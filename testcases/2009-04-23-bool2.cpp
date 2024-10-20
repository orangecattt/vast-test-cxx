// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
// g++.old-deja/g++.jason/bool2.C from gcc testsuite.
// Crashed before 67975 went in.
struct F {
  bool b1 : 1;
  bool b2 : 7;
};

int main()
{
  F f = { true, true };

  if (int (f.b1) != 1)
    return 1;
}
