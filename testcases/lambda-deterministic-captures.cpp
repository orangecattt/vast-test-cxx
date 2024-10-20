// RUN: %driver -cc1 %isys --std=c++17 %s %target -o %t%output-suffix && %filecheck

struct stream {
  friend const stream &operator<<(const stream &, const float &);
};

void foo() {
  constexpr float f_zero = 0.0f;
  constexpr float f_one = 1.0f;
  constexpr float f_two = 2.0f;

  stream s;
  [=]() {
    s << f_zero << f_one << f_two;
  }();
}

// CHECK: define{{.*}} void @_Z3foov
// CHECK: getelementptr inbounds %{{.+}}, ptr %{{.+}}, i32 0, i32 0
// CHECK-NEXT: getelementptr inbounds %{{.+}}, ptr %{{.+}}, i32 0, i32 1
// CHECK-NEXT: store float 0.000
// CHECK-NEXT: getelementptr inbounds %{{.+}}, ptr %{{.+}}, i32 0, i32 2
// CHECK-NEXT: store float 1.000
// CHECK-NEXT: getelementptr inbounds %{{.+}}, ptr %{{.+}}, i32 0, i32 3
// CHECK-NEXT: store float 2.000

// The lambda body.  Reverse iteration when the captures aren't deterministic
// causes these to be laid out differently in the lambda.
// CHECK: define internal void
// CHECK: getelementptr inbounds %{{.+}}, ptr %{{.+}}, i32 0, i32 0
// CHECK: getelementptr inbounds %{{.+}}, ptr %{{.+}}, i32 0, i32 1
// CHECK: getelementptr inbounds %{{.+}}, ptr %{{.+}}, i32 0, i32 2
// CHECK: getelementptr inbounds %{{.+}}, ptr %{{.+}}, i32 0, i32 3
