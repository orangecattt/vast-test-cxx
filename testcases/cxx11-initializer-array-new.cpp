// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck


struct S { S(); S(int); ~S(); int n; };

void *p = new S[2][3]{ { 1, 2, 3 }, { 4, 5, 6 } };


int n;
void *q = new S[n][3]{ { 1, 2, 3 }, { 4, 5, 6 } };


struct T { int a; };
void *r = new T[n][3]{ { 1, 2, 3 }, { 4, 5, 6 } };

