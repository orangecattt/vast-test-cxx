// RUN: %driver -cc1 %isys %s -fblocks %target -o %t%output-suffix && %filecheck

typedef void (^dispatch_block_t)(void);

void dispatch_once(dispatch_block_t);

class Zone {
public:
  Zone();
  ~Zone();
};

Zone::Zone() {
    dispatch_once(^{});
    dispatch_once(^{});
}

Zone::~Zone() {
    dispatch_once(^{});
    dispatch_once(^{});
}

class X : public virtual Zone {
  X();
  ~X();
};

X::X() {
    dispatch_once(^{});
    dispatch_once(^{});
};

X::~X() {
    dispatch_once(^{});
    dispatch_once(^{});
};


// CHECK-LABEL: define internal void @___ZN4ZoneC2Ev_block_invoke
// CHECK-LABEL: define internal void @___ZN4ZoneC2Ev_block_invoke_
// CHECK-LABEL: define internal void @___ZN4ZoneD2Ev_block_invoke
// CHECK-LABEL: define internal void @___ZN4ZoneD2Ev_block_invoke_
// CHECK-LABEL: define internal void @___ZN1XC2Ev_block_invoke
// CHECK-LABEL: define internal void @___ZN1XC2Ev_block_invoke_
// CHECK-LABEL: define internal void @___ZN1XD2Ev_block_invoke
// CHECK-LABEL: define internal void @___ZN1XD2Ev_block_invoke_
