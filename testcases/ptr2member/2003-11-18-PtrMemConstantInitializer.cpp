// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct Gfx {
  void opMoveSetShowText();
};

struct Operator {
  void (Gfx::*func)();
};

Operator opTab[] = {
  {&Gfx::opMoveSetShowText},
};
