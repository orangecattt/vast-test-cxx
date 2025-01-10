// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

class TestNaked {
public:
  void NakedFunction();
};

__attribute__((naked)) void TestNaked::NakedFunction() {
  asm("");
}
