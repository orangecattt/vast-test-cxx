// NOTE: Assertions have been autogenerated by utils/update_cc_test_checks.py
// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

extern volatile bool b;
extern volatile int i;
extern bool A();
extern bool B();

// CHECK-LABEL: @_Z1fv(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[RETVAL:%.*]] = alloca i1, align 1
// CHECK-NEXT:    [[TMP0:%.*]] = load volatile i8, ptr @b, align 1, !tbaa [[TBAA2:![0-9]+]], !range [[RNG6:![0-9]+]]
// CHECK-NEXT:    [[TOBOOL:%.*]] = trunc i8 [[TMP0]] to i1
// CHECK-NEXT:    [[TOBOOL_EXPVAL:%.*]] = call i1 @llvm.expect.i1(i1 [[TOBOOL]], i1 true)
// CHECK-NEXT:    br i1 [[TOBOOL_EXPVAL]], label [[IF_THEN:%.*]], label [[IF_END:%.*]]
// CHECK:       if.then:
// CHECK-NEXT:    [[CALL:%.*]] = call noundef zeroext i1 @_Z1Av()
// CHECK-NEXT:    store i1 [[CALL]], ptr [[RETVAL]], align 1
// CHECK-NEXT:    br label [[RETURN:%.*]]
// CHECK:       if.end:
// CHECK-NEXT:    [[CALL1:%.*]] = call noundef zeroext i1 @_Z1Bv()
// CHECK-NEXT:    store i1 [[CALL1]], ptr [[RETVAL]], align 1
// CHECK-NEXT:    br label [[RETURN]]
// CHECK:       return:
// CHECK-NEXT:    [[TMP1:%.*]] = load i1, ptr [[RETVAL]], align 1
// CHECK-NEXT:    ret i1 [[TMP1]]
//
bool f() {
  if (b)
    [[likely]] {
      return A();
    }
  return B();
}

// CHECK-LABEL: @_Z1gv(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[RETVAL:%.*]] = alloca i1, align 1
// CHECK-NEXT:    [[TMP0:%.*]] = load volatile i8, ptr @b, align 1, !tbaa [[TBAA2]], !range [[RNG6]]
// CHECK-NEXT:    [[TOBOOL:%.*]] = trunc i8 [[TMP0]] to i1
// CHECK-NEXT:    [[TOBOOL_EXPVAL:%.*]] = call i1 @llvm.expect.i1(i1 [[TOBOOL]], i1 false)
// CHECK-NEXT:    br i1 [[TOBOOL_EXPVAL]], label [[IF_THEN:%.*]], label [[IF_END:%.*]]
// CHECK:       if.then:
// CHECK-NEXT:    [[CALL:%.*]] = call noundef zeroext i1 @_Z1Av()
// CHECK-NEXT:    store i1 [[CALL]], ptr [[RETVAL]], align 1
// CHECK-NEXT:    br label [[RETURN:%.*]]
// CHECK:       if.end:
// CHECK-NEXT:    [[CALL1:%.*]] = call noundef zeroext i1 @_Z1Bv()
// CHECK-NEXT:    store i1 [[CALL1]], ptr [[RETVAL]], align 1
// CHECK-NEXT:    br label [[RETURN]]
// CHECK:       return:
// CHECK-NEXT:    [[TMP1:%.*]] = load i1, ptr [[RETVAL]], align 1
// CHECK-NEXT:    ret i1 [[TMP1]]
//
bool g() {
  if (b)
    [[unlikely]] {
      return A();
    }

  return B();
}

// CHECK-LABEL: @_Z1hv(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[RETVAL:%.*]] = alloca i1, align 1
// CHECK-NEXT:    [[TMP0:%.*]] = load volatile i8, ptr @b, align 1, !tbaa [[TBAA2]], !range [[RNG6]]
// CHECK-NEXT:    [[TOBOOL:%.*]] = trunc i8 [[TMP0]] to i1
// CHECK-NEXT:    [[TOBOOL_EXPVAL:%.*]] = call i1 @llvm.expect.i1(i1 [[TOBOOL]], i1 false)
// CHECK-NEXT:    br i1 [[TOBOOL_EXPVAL]], label [[IF_THEN:%.*]], label [[IF_END:%.*]]
// CHECK:       if.then:
// CHECK-NEXT:    [[CALL:%.*]] = call noundef zeroext i1 @_Z1Av()
// CHECK-NEXT:    store i1 [[CALL]], ptr [[RETVAL]], align 1
// CHECK-NEXT:    br label [[RETURN:%.*]]
// CHECK:       if.end:
// CHECK-NEXT:    [[CALL1:%.*]] = call noundef zeroext i1 @_Z1Bv()
// CHECK-NEXT:    store i1 [[CALL1]], ptr [[RETVAL]], align 1
// CHECK-NEXT:    br label [[RETURN]]
// CHECK:       return:
// CHECK-NEXT:    [[TMP1:%.*]] = load i1, ptr [[RETVAL]], align 1
// CHECK-NEXT:    ret i1 [[TMP1]]
//
bool h() {
  if (b)
    [[unlikely]] return A();

  return B();
}

// CHECK-LABEL: @_Z8NullStmtv(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load volatile i8, ptr @b, align 1, !tbaa [[TBAA2]], !range [[RNG6]]
// CHECK-NEXT:    [[TOBOOL:%.*]] = trunc i8 [[TMP0]] to i1
// CHECK-NEXT:    [[TOBOOL_EXPVAL:%.*]] = call i1 @llvm.expect.i1(i1 [[TOBOOL]], i1 false)
// CHECK-NEXT:    br i1 [[TOBOOL_EXPVAL]], label [[IF_THEN:%.*]], label [[IF_ELSE:%.*]]
// CHECK:       if.then:
// CHECK-NEXT:    br label [[IF_END:%.*]]
// CHECK:       if.else:
// CHECK-NEXT:    store volatile i8 1, ptr @b, align 1, !tbaa [[TBAA2]]
// CHECK-NEXT:    br label [[IF_END]]
// CHECK:       if.end:
// CHECK-NEXT:    ret void
//
void NullStmt() {
  if (b)
    [[unlikely]];
  else {
    // Make sure the branches aren't optimized away.
    b = true;
  }
}

// CHECK-LABEL: @_Z6IfStmtv(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load volatile i8, ptr @b, align 1, !tbaa [[TBAA2]], !range [[RNG6]]
// CHECK-NEXT:    [[TOBOOL:%.*]] = trunc i8 [[TMP0]] to i1
// CHECK-NEXT:    [[TOBOOL_EXPVAL:%.*]] = call i1 @llvm.expect.i1(i1 [[TOBOOL]], i1 false)
// CHECK-NEXT:    br i1 [[TOBOOL_EXPVAL]], label [[IF_THEN:%.*]], label [[IF_END2:%.*]]
// CHECK:       if.then:
// CHECK-NEXT:    [[CALL:%.*]] = call noundef zeroext i1 @_Z1Bv()
// CHECK-NEXT:    br i1 [[CALL]], label [[IF_THEN1:%.*]], label [[IF_END:%.*]]
// CHECK:       if.then1:
// CHECK-NEXT:    br label [[IF_END]]
// CHECK:       if.end:
// CHECK-NEXT:    br label [[IF_END2]]
// CHECK:       if.end2:
// CHECK-NEXT:    [[TMP1:%.*]] = load volatile i8, ptr @b, align 1, !tbaa [[TBAA2]], !range [[RNG6]]
// CHECK-NEXT:    [[TOBOOL3:%.*]] = trunc i8 [[TMP1]] to i1
// CHECK-NEXT:    br i1 [[TOBOOL3]], label [[IF_THEN4:%.*]], label [[IF_END8:%.*]]
// CHECK:       if.then4:
// CHECK-NEXT:    [[CALL5:%.*]] = call noundef zeroext i1 @_Z1Bv()
// CHECK-NEXT:    [[CALL5_EXPVAL:%.*]] = call i1 @llvm.expect.i1(i1 [[CALL5]], i1 false)
// CHECK-NEXT:    br i1 [[CALL5_EXPVAL]], label [[IF_THEN6:%.*]], label [[IF_END7:%.*]]
// CHECK:       if.then6:
// CHECK-NEXT:    store volatile i8 0, ptr @b, align 1, !tbaa [[TBAA2]]
// CHECK-NEXT:    br label [[IF_END7]]
// CHECK:       if.end7:
// CHECK-NEXT:    br label [[IF_END8]]
// CHECK:       if.end8:
// CHECK-NEXT:    ret void
//
void IfStmt() {
  if (b)
    [[unlikely]] if (B()) {}

  if (b) {
    if (B())
      [[unlikely]] { b = false; }
  }
}

// CHECK-LABEL: @_Z9WhileStmtv(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load volatile i8, ptr @b, align 1, !tbaa [[TBAA2]], !range [[RNG6]]
// CHECK-NEXT:    [[TOBOOL:%.*]] = trunc i8 [[TMP0]] to i1
// CHECK-NEXT:    [[TOBOOL_EXPVAL:%.*]] = call i1 @llvm.expect.i1(i1 [[TOBOOL]], i1 false)
// CHECK-NEXT:    br i1 [[TOBOOL_EXPVAL]], label [[IF_THEN:%.*]], label [[IF_END:%.*]]
// CHECK:       if.then:
// CHECK-NEXT:    br label [[WHILE_COND:%.*]]
// CHECK:       while.cond:
// CHECK-NEXT:    [[CALL:%.*]] = call noundef zeroext i1 @_Z1Bv()
// CHECK-NEXT:    br i1 [[CALL]], label [[WHILE_BODY:%.*]], label [[WHILE_END:%.*]]
// CHECK:       while.body:
// CHECK-NEXT:    br label [[WHILE_COND]], !llvm.loop [[LOOP7:![0-9]+]]
// CHECK:       while.end:
// CHECK-NEXT:    br label [[IF_END]]
// CHECK:       if.end:
// CHECK-NEXT:    [[TMP1:%.*]] = load volatile i8, ptr @b, align 1, !tbaa [[TBAA2]], !range [[RNG6]]
// CHECK-NEXT:    [[TOBOOL1:%.*]] = trunc i8 [[TMP1]] to i1
// CHECK-NEXT:    br i1 [[TOBOOL1]], label [[IF_THEN2:%.*]], label [[IF_END7:%.*]]
// CHECK:       if.then2:
// CHECK-NEXT:    br label [[WHILE_COND3:%.*]]
// CHECK:       while.cond3:
// CHECK-NEXT:    [[CALL4:%.*]] = call noundef zeroext i1 @_Z1Bv()
// CHECK-NEXT:    [[CALL4_EXPVAL:%.*]] = call i1 @llvm.expect.i1(i1 [[CALL4]], i1 false)
// CHECK-NEXT:    br i1 [[CALL4_EXPVAL]], label [[WHILE_BODY5:%.*]], label [[WHILE_END6:%.*]]
// CHECK:       while.body5:
// CHECK-NEXT:    store volatile i8 0, ptr @b, align 1, !tbaa [[TBAA2]]
// CHECK-NEXT:    br label [[WHILE_COND3]], !llvm.loop [[LOOP10:![0-9]+]]
// CHECK:       while.end6:
// CHECK-NEXT:    br label [[IF_END7]]
// CHECK:       if.end7:
// CHECK-NEXT:    ret void
//
void WhileStmt() {
  if (b)
    [[unlikely]] while (B()) {}

  if (b)
    while (B())
      [[unlikely]] { b = false; }
}

// CHECK-LABEL: @_Z6DoStmtv(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load volatile i8, ptr @b, align 1, !tbaa [[TBAA2]], !range [[RNG6]]
// CHECK-NEXT:    [[TOBOOL:%.*]] = trunc i8 [[TMP0]] to i1
// CHECK-NEXT:    [[TOBOOL_EXPVAL:%.*]] = call i1 @llvm.expect.i1(i1 [[TOBOOL]], i1 false)
// CHECK-NEXT:    br i1 [[TOBOOL_EXPVAL]], label [[IF_THEN:%.*]], label [[IF_END:%.*]]
// CHECK:       if.then:
// CHECK-NEXT:    br label [[DO_BODY:%.*]]
// CHECK:       do.body:
// CHECK-NEXT:    br label [[DO_COND:%.*]]
// CHECK:       do.cond:
// CHECK-NEXT:    [[CALL:%.*]] = call noundef zeroext i1 @_Z1Bv()
// CHECK-NEXT:    br i1 [[CALL]], label [[DO_BODY]], label [[DO_END:%.*]], !llvm.loop [[LOOP11:![0-9]+]]
// CHECK:       do.end:
// CHECK-NEXT:    br label [[IF_END]]
// CHECK:       if.end:
// CHECK-NEXT:    [[TMP1:%.*]] = load volatile i8, ptr @b, align 1, !tbaa [[TBAA2]], !range [[RNG6]]
// CHECK-NEXT:    [[TOBOOL1:%.*]] = trunc i8 [[TMP1]] to i1
// CHECK-NEXT:    br i1 [[TOBOOL1]], label [[IF_THEN2:%.*]], label [[IF_END7:%.*]]
// CHECK:       if.then2:
// CHECK-NEXT:    br label [[DO_BODY3:%.*]]
// CHECK:       do.body3:
// CHECK-NEXT:    br label [[DO_COND4:%.*]]
// CHECK:       do.cond4:
// CHECK-NEXT:    [[CALL5:%.*]] = call noundef zeroext i1 @_Z1Bv()
// CHECK-NEXT:    br i1 [[CALL5]], label [[DO_BODY3]], label [[DO_END6:%.*]], !llvm.loop [[LOOP12:![0-9]+]]
// CHECK:       do.end6:
// CHECK-NEXT:    br label [[IF_END7]]
// CHECK:       if.end7:
// CHECK-NEXT:    ret void
//
void DoStmt() {
  if (b)
    [[unlikely]] do {}
    while (B())
      ;

  if (b)
    do
      [[unlikely]] {}
    while (B());
}

// CHECK-LABEL: @_Z7ForStmtv(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load volatile i8, ptr @b, align 1, !tbaa [[TBAA2]], !range [[RNG6]]
// CHECK-NEXT:    [[TOBOOL:%.*]] = trunc i8 [[TMP0]] to i1
// CHECK-NEXT:    [[TOBOOL_EXPVAL:%.*]] = call i1 @llvm.expect.i1(i1 [[TOBOOL]], i1 false)
// CHECK-NEXT:    br i1 [[TOBOOL_EXPVAL]], label [[IF_THEN:%.*]], label [[IF_END:%.*]]
// CHECK:       if.then:
// CHECK-NEXT:    br label [[FOR_COND:%.*]]
// CHECK:       for.cond:
// CHECK-NEXT:    [[CALL:%.*]] = call noundef zeroext i1 @_Z1Bv()
// CHECK-NEXT:    br i1 [[CALL]], label [[FOR_BODY:%.*]], label [[FOR_END:%.*]]
// CHECK:       for.body:
// CHECK-NEXT:    br label [[FOR_COND]], !llvm.loop [[LOOP13:![0-9]+]]
// CHECK:       for.end:
// CHECK-NEXT:    br label [[IF_END]]
// CHECK:       if.end:
// CHECK-NEXT:    [[TMP1:%.*]] = load volatile i8, ptr @b, align 1, !tbaa [[TBAA2]], !range [[RNG6]]
// CHECK-NEXT:    [[TOBOOL1:%.*]] = trunc i8 [[TMP1]] to i1
// CHECK-NEXT:    br i1 [[TOBOOL1]], label [[IF_THEN2:%.*]], label [[IF_END7:%.*]]
// CHECK:       if.then2:
// CHECK-NEXT:    br label [[FOR_COND3:%.*]]
// CHECK:       for.cond3:
// CHECK-NEXT:    [[CALL4:%.*]] = call noundef zeroext i1 @_Z1Bv()
// CHECK-NEXT:    [[CALL4_EXPVAL:%.*]] = call i1 @llvm.expect.i1(i1 [[CALL4]], i1 false)
// CHECK-NEXT:    br i1 [[CALL4_EXPVAL]], label [[FOR_BODY5:%.*]], label [[FOR_END6:%.*]]
// CHECK:       for.body5:
// CHECK-NEXT:    br label [[FOR_COND3]], !llvm.loop [[LOOP14:![0-9]+]]
// CHECK:       for.end6:
// CHECK-NEXT:    br label [[IF_END7]]
// CHECK:       if.end7:
// CHECK-NEXT:    ret void
//
void ForStmt() {
  if (b)
    [[unlikely]] for (; B();) {}

  if (b)
    for (; B();)
      [[unlikely]] {}
}

// CHECK-LABEL: @_Z8GotoStmtv(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load volatile i8, ptr @b, align 1, !tbaa [[TBAA2]], !range [[RNG6]]
// CHECK-NEXT:    [[TOBOOL:%.*]] = trunc i8 [[TMP0]] to i1
// CHECK-NEXT:    [[TOBOOL_EXPVAL:%.*]] = call i1 @llvm.expect.i1(i1 [[TOBOOL]], i1 false)
// CHECK-NEXT:    br i1 [[TOBOOL_EXPVAL]], label [[IF_THEN:%.*]], label [[IF_ELSE:%.*]]
// CHECK:       if.then:
// CHECK-NEXT:    br label [[END:%.*]]
// CHECK:       if.else:
// CHECK-NEXT:    store volatile i8 1, ptr @b, align 1, !tbaa [[TBAA2]]
// CHECK-NEXT:    br label [[IF_END:%.*]]
// CHECK:       if.end:
// CHECK-NEXT:    br label [[END]]
// CHECK:       end:
// CHECK-NEXT:    ret void
//
void GotoStmt() {
  if (b)
    [[unlikely]] goto end;
  else {
    // Make sure the branches aren't optimized away.
    b = true;
  }
end:;
}

// CHECK-LABEL: @_Z10ReturnStmtv(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load volatile i8, ptr @b, align 1, !tbaa [[TBAA2]], !range [[RNG6]]
// CHECK-NEXT:    [[TOBOOL:%.*]] = trunc i8 [[TMP0]] to i1
// CHECK-NEXT:    [[TOBOOL_EXPVAL:%.*]] = call i1 @llvm.expect.i1(i1 [[TOBOOL]], i1 false)
// CHECK-NEXT:    br i1 [[TOBOOL_EXPVAL]], label [[IF_THEN:%.*]], label [[IF_ELSE:%.*]]
// CHECK:       if.then:
// CHECK-NEXT:    br label [[IF_END:%.*]]
// CHECK:       if.else:
// CHECK-NEXT:    store volatile i8 1, ptr @b, align 1, !tbaa [[TBAA2]]
// CHECK-NEXT:    br label [[IF_END]]
// CHECK:       if.end:
// CHECK-NEXT:    ret void
//
void ReturnStmt() {
  if (b)
    [[unlikely]] return;
  else {
    // Make sure the branches aren't optimized away.
    b = true;
  }
}

// CHECK-LABEL: @_Z10SwitchStmtv(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[TMP0:%.*]] = load volatile i8, ptr @b, align 1, !tbaa [[TBAA2]], !range [[RNG6]]
// CHECK-NEXT:    [[TOBOOL:%.*]] = trunc i8 [[TMP0]] to i1
// CHECK-NEXT:    [[TOBOOL_EXPVAL:%.*]] = call i1 @llvm.expect.i1(i1 [[TOBOOL]], i1 false)
// CHECK-NEXT:    br i1 [[TOBOOL_EXPVAL]], label [[IF_THEN:%.*]], label [[IF_ELSE:%.*]]
// CHECK:       if.then:
// CHECK-NEXT:    [[TMP1:%.*]] = load volatile i32, ptr @i, align 4, !tbaa [[TBAA15:![0-9]+]]
// CHECK-NEXT:    switch i32 [[TMP1]], label [[SW_EPILOG:%.*]] [
// CHECK-NEXT:    ]
// CHECK:       sw.epilog:
// CHECK-NEXT:    br label [[IF_END:%.*]]
// CHECK:       if.else:
// CHECK-NEXT:    store volatile i8 1, ptr @b, align 1, !tbaa [[TBAA2]]
// CHECK-NEXT:    br label [[IF_END]]
// CHECK:       if.end:
// CHECK-NEXT:    [[TMP2:%.*]] = load volatile i8, ptr @b, align 1, !tbaa [[TBAA2]], !range [[RNG6]]
// CHECK-NEXT:    [[TOBOOL1:%.*]] = trunc i8 [[TMP2]] to i1
// CHECK-NEXT:    br i1 [[TOBOOL1]], label [[IF_THEN2:%.*]], label [[IF_ELSE4:%.*]]
// CHECK:       if.then2:
// CHECK-NEXT:    [[TMP3:%.*]] = load volatile i32, ptr @i, align 4, !tbaa [[TBAA15]]
// CHECK-NEXT:    switch i32 [[TMP3]], label [[SW_EPILOG3:%.*]] [
// CHECK-NEXT:    ]
// CHECK:       sw.epilog3:
// CHECK-NEXT:    br label [[IF_END5:%.*]]
// CHECK:       if.else4:
// CHECK-NEXT:    store volatile i8 1, ptr @b, align 1, !tbaa [[TBAA2]]
// CHECK-NEXT:    br label [[IF_END5]]
// CHECK:       if.end5:
// CHECK-NEXT:    ret void
//
void SwitchStmt() {
  if (b)
    [[unlikely]] switch (i) {}
  else {
    // Make sure the branches aren't optimized away.
    b = true;
  }
  if (b)
    switch (i)
      [[unlikely]] {}
  else {
    // Make sure the branches aren't optimized away.
    b = true;
  }
}

