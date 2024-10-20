// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
// PR9178

void abort() __attribute__((__noreturn__));
struct CoinModelLink {
  CoinModelLink();
  ~CoinModelLink();
};
class CoinModel {
  CoinModelLink firstInQuadraticColumn();
};
CoinModelLink CoinModel::firstInQuadraticColumn() {
  abort();
  CoinModelLink x;
  return x;
}

