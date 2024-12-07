// RUN: %driver -cc1 %isys -std=c++2a %s -w %target -o %t%output-suffix && %filecheck


void f() {
  for (int arr[3] = {1, 2, 3}; int a : arr)
    ;
}
