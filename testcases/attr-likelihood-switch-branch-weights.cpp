// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

extern volatile int i;

void OneCaseL() {
  switch (i) {
    [[likely]] case 1: break;
  }
}

void OneCaseU() {
  switch (i) {
    [[unlikely]] case 1: ++i; break;
  }
}

void TwoCasesLN() {
  switch (i) {
    [[likely]] case 1: break;
    case 2: break;
  }
}

void TwoCasesUN() {
  switch (i) {
    [[unlikely]] case 1: break;
    case 2: break;
  }
}

void TwoCasesLU() {
  switch (i) {
    [[likely]] case 1: break;
    [[unlikely]] case 2: break;
  }
}

void CasesFallthroughNNLN() {
  switch (i) {
    case 1:
    case 2:
    [[likely]] case 3:
    case 4: break;
  }
}

void CasesFallthroughNNUN() {
  switch (i) {
    case 1:
    case 2:
    [[unlikely]] case 3:
    case 4: break;
  }
}

void CasesFallthroughRangeSmallLN() {
  switch (i) {
    case 1 ... 5: ++i;
    case 102:
    [[likely]] case 103:
    case 104: break;
  }
}

void CasesFallthroughRangeSmallUN() {
  switch (i) {
    case 1 ... 5: ++i;
    case 102:
    [[unlikely]] case 103:
    case 104: break;
  }
}

void CasesFallthroughRangeLargeLLN() {
  switch (i) {
    [[likely]] case 0 ... 64:
    [[likely]] case 1003:
    case 104: break;
  }
}

void CasesFallthroughRangeLargeUUN() {
  switch (i) {
    [[unlikely]] case 0 ... 64:
    [[unlikely]] case 1003:
    case 104: break;
  }
}

void OneCaseDefaultL() {
  switch (i) {
    case 1: break;
    [[likely]] default: break;
  }
}

void OneCaseDefaultU() {
  switch (i) {
    case 1: break;
    [[unlikely]] default: break;
  }
}

void TwoCasesDefaultLNL() {
  switch (i) {
    [[likely]] case 1: break;
    case 2: break;
    [[likely]] default: break;
  }
}

void TwoCasesDefaultLNN() {
  switch (i) {
    [[likely]] case 1: break;
    case 2: break;
    default: break;
  }
}

void TwoCasesDefaultLNU() {
  switch (i) {
    [[likely]] case 1: break;
    case 2: break;
    [[unlikely]] default: break;
  }
}
