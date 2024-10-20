// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

void pipeline_disabled(int *List, int Length, int Value) {
#pragma clang loop pipeline(disable)
  for (int i = 0; i < Length; i++) {
    List[i] = Value;
  }
}

void pipeline_not_disabled(int *List, int Length, int Value) {
  for (int i = 0; i < Length; i++) {
    List[i] = Value;
  }
}

void pipeline_initiation_interval(int *List, int Length, int Value) {
#pragma clang loop pipeline_initiation_interval(10)
  for (int i = 0; i < Length; i++) {
    List[i] = Value;
  }
}

void pipeline_disabled_on_nested_loop(int *List, int Length, int Value) {
  for (int i = 0; i < Length; i++) {
#pragma clang loop pipeline(disable)
    for (int j = 0; j < Length; j++) {
      List[i * Length + j] = Value;
    }
  }
}




