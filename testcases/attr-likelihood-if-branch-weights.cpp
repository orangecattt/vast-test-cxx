// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

extern volatile bool b;
extern volatile int i;
extern bool A();
extern bool B();

bool f() {
  if (b)
    [[likely]] {
      return A();
    }
  return B();
}

bool g() {
  if (b)
    [[unlikely]] {
      return A();
    }

  return B();
}

bool h() {
  if (b)
    [[unlikely]] return A();

  return B();
}

void NullStmt() {
  if (b)
    [[unlikely]];
  else {
    b = true;
  }
}

void IfStmt() {
  if (b)
    [[unlikely]] if (B()) {}

  if (b) {
    if (B())
      [[unlikely]] { b = false; }
  }
}

void WhileStmt() {
  if (b)
    [[unlikely]] while (B()) {}

  if (b)
    while (B())
      [[unlikely]] { b = false; }
}

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

void ForStmt() {
  if (b)
    [[unlikely]] for (; B();) {}

  if (b)
    for (; B();)
      [[unlikely]] {}
}

void GotoStmt() {
  if (b)
    [[unlikely]] goto end;
  else {
    b = true;
  }
end:;
}

void ReturnStmt() {
  if (b)
    [[unlikely]] return;
  else {
    b = true;
  }
}

void SwitchStmt() {
  if (b)
    [[unlikely]] switch (i) {}
  else {
    b = true;
  }
  if (b)
    switch (i)
      [[unlikely]] {}
  else {
    b = true;
  }
}

