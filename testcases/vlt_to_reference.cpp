// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

// CHECK-LABEL: @main

struct dyn_array { 
    int size;
    int data[];
};

int foo(dyn_array **&d) {
  return (*d)->data[1];
}

int main()
{
    dyn_array **d;
    return foo(d);

    // CHECK: call {{.+}} @{{.+}}foo{{.+}}(
    // CHECK: ret i{{[0-9]+}}
}

