// RUN: %driver -cc1 %isys %std_cxx11- -Wno-dynamic-exception-spec %s %target -o %t%output-suffix && %filecheck

void g();

// CHECK: define{{.*}} void @_Z1fv() [[NUW:#[0-9]+]]
void f() throw (int) { 

  // CHECK-NOT: invoke void @_Z1gv
  g();
  // CHECK: call void @_Z1gv()
  // CHECK: ret void
}

// CHECK: attributes [[NUW]] = { mustprogress noinline nounwind{{.*}} }
