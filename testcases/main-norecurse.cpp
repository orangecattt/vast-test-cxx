// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

// CHECK: define {{.*}} @main({{.*}}) #0
int main(int argc, char **argv) {
    return 1;
}

// CHECK: attributes #0 = { mustprogress noinline norecurse{{.*}} }
