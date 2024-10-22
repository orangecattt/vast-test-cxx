// RUN: %driver -cc1 %isys -mno-constructor-aliases -mconstructor-aliases %s %target -o %t%output-suffix && %filecheck


struct B {
  B();
};
B::B() {
}

