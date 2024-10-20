// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck


extern bool a();
extern bool b();
extern bool c();

void ab1(int &i) {
  if (__builtin_expect(a() && b() && a(), 1)) {
    ++i;
  } else {
    --i;
  }
}

void al(int &i) {
  if (a() && b() && c()) [[likely]] {
    ++i;
  } else {
    --i;
  }
}

void ab0(int &i) {
  if (__builtin_expect(a() && b() && c(), 0)) {
    ++i;
  } else {
    --i;
  }
}

void au(int &i) {
  if (a() && b() && c()) [[unlikely]] {
    ++i;
  } else {
    --i;
  }
}

void ob1(int &i) {
  if (__builtin_expect(a() || b() || a(), 1)) {
    i = 0;
  } else {
    --i;
  }
}

void ol(int &i) {
  if (a() || b() || c()) [[likely]] {
    i = 0;
  } else {
    --i;
  }
}

void ob0(int &i) {
  if (__builtin_expect(a() || b() || c(), 0)) {
    i = 0;
  } else {
    --i;
  }
}

void ou(int &i) {
  if (a() || b() || c()) [[unlikely]] {
    i = 0;
  } else {
    --i;
  }
}

void nb1(int &i) {
  if (__builtin_expect(!a(), 1)) {
    ++i;
  } else {
    --i;
  }
}

void nl(int &i) {
  if (bool d = !a()) [[likely]] {
    ++i;
  } else {
    --i;
  }
}

void nb0(int &i) {
  if (__builtin_expect(!a(), 0)) {
    ++i;
  } else {
    --i;
  }
}

void nu(int &i) {
  if (bool d = !a()) [[unlikely]] {
    ++i;
  } else {
    --i;
  }
}

void tb1(int &i) {
  if (__builtin_expect(a() ? b() : c(), 1)) {
    ++i;
  } else {
    --i;
  }
}

void tl(int &i) {
  if (bool d = a() ? b() : c()) [[likely]] {
    ++i;
  } else {
    --i;
  }
}

void tl2(int &i) {
  if (a() ? b() : c()) [[likely]] {
    ++i;
  } else {
    --i;
  }
}

void tb0(int &i) {
  if (__builtin_expect(a() ? b() : c(), 0)) {
    ++i;
  } else {
    --i;
  }
}

void tu(int &i) {
  if (bool d = a() ? b() : c()) [[unlikely]] {
    ++i;
  } else {
    --i;
  }
}

void tu2(int &i) {
  if (a() ? b() : c()) [[unlikely]] {
    ++i;
  } else {
    --i;
  }
}

