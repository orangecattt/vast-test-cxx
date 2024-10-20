// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct X {
  X();
  ~X();
};

struct Y {
  X get();
};

struct X2 {
  X x;
};

template<typename T>
void call() {
  Y().get();
}

template void call<int>();  

template<typename T>
void compound_literal() {
  (X2){};
}

template void compound_literal<int>();  

