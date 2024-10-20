// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -fno-assume-sane-operator-new %s %target -o %t%output-suffix && %filecheck

class teste {
  int A;
public:
  teste() : A(2) {}
};

void f1() {
  // ALL: declare noundef nonnull ptr @_Znwj(
  new teste();
}

// operator new should check for overflow in multiply.
void *f2(long N) {
  return new int[N];

  // ALL:      [[UWO:%.*]] = call {{.*}} @llvm.umul.with.overflow
  // ALL-NEXT: [[OVER:%.*]] = extractvalue {{.*}} [[UWO]], 1
  // ALL-NEXT: [[SUM:%.*]] = extractvalue {{.*}} [[UWO]], 0
  // ALL-NEXT: [[RESULT:%.*]] = select i1 [[OVER]], i32 -1, i32 [[SUM]]
  // SANE-NEXT: call noalias noundef nonnull ptr @_Znaj(i32 noundef [[RESULT]])
  // SANENOT-NEXT: call noundef nonnull ptr @_Znaj(i32 noundef [[RESULT]])
}

// ALL: declare noundef nonnull ptr @_Znaj(
