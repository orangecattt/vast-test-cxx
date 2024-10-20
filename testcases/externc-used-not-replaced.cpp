// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

extern "C" {
  const char a __attribute__((used)){};
}

