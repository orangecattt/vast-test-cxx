// RUN: %driver -cc1 %isys %s -fexceptions -fcxx-exceptions -mllvm -simplifycfg-sink-common=false %target -o %t%output-suffix && %filecheck

struct Large {
  int cs[32];
};

Large getLarge();

struct NontrivialDtor {
  int i;
  ~NontrivialDtor();
};

void cleanupsAreEmittedWithoutTryCatch() {

  NontrivialDtor clean;

  getLarge();
  getLarge();
}

void cleanupsAreEmittedWithTryCatch() {

  NontrivialDtor clean;

  try {
    getLarge();
    getLarge();
  } catch (...) {}

  getLarge();
}

void cleanupInTryHappensBeforeCleanupInCatch() {

  try {
    getLarge();
  } catch (const int &) {
    getLarge();
  } catch (...) {
    getLarge();
  }
}

