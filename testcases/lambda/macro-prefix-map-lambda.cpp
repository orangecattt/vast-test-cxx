// RUN: %driver -cc1 %isys -fmacro-prefix-map=%p=./UNLIKELY_PATH/empty %s %target -o %t%output-suffix && %filecheck

template<typename f>
auto lambdatest(f&& cb) {
  const char *s = __PRETTY_FUNCTION__;
  return s;
}

int main() {
  auto *s = lambdatest([](){});

  return 0;
}
