// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++14 %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++17 %s %target -o %t%output-suffix && %filecheck

// CHECK: struct.a
typedef struct { } a;
typedef struct {
  a b[];
} c;

// CHECK: {{(dso_local )?}}global %struct.c{{.*}}zeroinitializer
c d{ };
