// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

class TestNaked {
public:
  void NakedFunction();
};

__attribute__((naked)) void TestNaked::NakedFunction() {
  // CHECK-LABEL: define {{(dso_local )?}}{{(x86_thiscallcc )?}}void @
  // CHECK: call void asm sideeffect
  asm("");
}
