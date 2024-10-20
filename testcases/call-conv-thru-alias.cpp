// RUN: %driver -cc1 %isys -mconstructor-aliases %s %target -o %t%output-suffix && %filecheck

struct Base { virtual ~Base(); };
struct Derived : Base {
  virtual ~Derived();
  static Derived inst;
};

Base::~Base(){}
Derived::~Derived(){}
Derived Derived::inst;

// CHECK: @"??1Derived@@UAE@XZ" = dso_local unnamed_addr alias void (ptr), ptr @"??1Base@@UAE@XZ"

// CHECK: define dso_local x86_thiscallcc void @"??1Base@@UAE@XZ"
// CHECK: define internal void @"??__E?inst@Derived@@2U1@A@@YAXXZ"
// CHECK: call i32 @atexit(ptr @"??__F?inst@Derived@@2U1@A@@YAXXZ"
//
// CHECK: define internal void @"??__F?inst@Derived@@2U1@A@@YAXXZ"
// CHECK-NEXT: entry:
// CHECK-NEXT: call x86_thiscallcc void @"??1Derived@@UAE@XZ"
