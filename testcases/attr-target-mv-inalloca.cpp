// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

struct Foo {
  Foo();
  Foo(const Foo &o);
  ~Foo();
  int x;
};
int __attribute__((target("default"))) bar(Foo o) { return o.x; }
int __attribute__((target("sse4.2"))) bar(Foo o) { return o.x + 1; }
int __attribute__((target("arch=ivybridge"))) bar(Foo o) { return o.x + 2; }

void usage() {
  Foo f;
  bar(f);
}

// DARWIN-NOT: inalloca(
// LINUX-NOT: inalloca(

// WINDOWS: define dso_local noundef i32 @"?bar@@YAHUFoo@@@Z"(ptr inalloca(<{ %struct.Foo }>) %0)
// WINDOWS: %[[O:[0-9a-zA-Z]+]] = getelementptr inbounds <{ %struct.Foo }>, ptr %0, i32 0, i32 0
// WINDOWS: %[[X:[0-9a-zA-Z]+]] = getelementptr inbounds %struct.Foo, ptr %[[O]], i32 0, i32 0
// WINDOWS: %[[LOAD:[0-9a-zA-Z]+]] = load i32, ptr %[[X]]
// WINDOWS: ret i32 %[[LOAD]]

// WINDOWS: define dso_local noundef i32 @"?bar@@YAHUFoo@@@Z.sse4.2"(ptr inalloca(<{ %struct.Foo }>) %0)
// WINDOWS: %[[O:[0-9a-zA-Z]+]] = getelementptr inbounds <{ %struct.Foo }>, ptr %0, i32 0, i32 0
// WINDOWS: %[[X:[0-9a-zA-Z]+]] = getelementptr inbounds %struct.Foo, ptr %[[O]], i32 0, i32 0
// WINDOWS: %[[LOAD:[0-9a-zA-Z]+]] = load i32, ptr %[[X]]
// WINDOWS: %[[ADD:[0-9a-zA-Z]+]] = add nsw i32 %[[LOAD]], 1
// WINDOWS: ret i32 %[[ADD]]

// WINDOWS: define dso_local noundef i32 @"?bar@@YAHUFoo@@@Z.arch_ivybridge"(ptr inalloca(<{ %struct.Foo }>) %0)
// WINDOWS: %[[O:[0-9a-zA-Z]+]] = getelementptr inbounds <{ %struct.Foo }>, ptr %0, i32 0, i32 0
// WINDOWS: %[[X:[0-9a-zA-Z]+]] = getelementptr inbounds %struct.Foo, ptr %[[O]], i32 0, i32 0
// WINDOWS: %[[LOAD:[0-9a-zA-Z]+]] = load i32, ptr %[[X]]
// WINDOWS: %[[ADD:[0-9a-zA-Z]+]] = add nsw i32 %[[LOAD]], 2
// WINDOWS: ret i32 %[[ADD]]

// WINDOWS: define dso_local void @"?usage@@YAXXZ"()
// WINDOWS: %[[F:[0-9a-zA-Z]+]] = alloca %struct.Foo
// WINDOWS: %[[ARGMEM:[0-9a-zA-Z]+]] = alloca inalloca <{ %struct.Foo }>
// WINDOWS: %[[CALL:[0-9a-zA-Z]+]] = call noundef i32 @"?bar@@YAHUFoo@@@Z.resolver"(ptr inalloca(<{ %struct.Foo }>) %[[ARGMEM]])

// WINDOWS: define weak_odr dso_local i32 @"?bar@@YAHUFoo@@@Z.resolver"(ptr %0)
// WINDOWS: %[[RET:[0-9a-zA-Z]+]] = musttail call i32 @"?bar@@YAHUFoo@@@Z.arch_ivybridge"(ptr %0)
// WINDOWS-NEXT: ret i32 %[[RET]]
// WINDOWS: %[[RET:[0-9a-zA-Z]+]] = musttail call i32 @"?bar@@YAHUFoo@@@Z.sse4.2"(ptr %0)
// WINDOWS-NEXT: ret i32 %[[RET]]
// WINDOWS: %[[RET:[0-9a-zA-Z]+]] = musttail call i32 @"?bar@@YAHUFoo@@@Z"(ptr %0)
// WINDOWS-NEXT: ret i32 %[[RET]]


// WINDOWS64: define dso_local noundef i32 @"?bar@@YAHUFoo@@@Z"(ptr noundef %[[O:[0-9a-zA-Z]+]])
// WINDOWS64: %[[X:[0-9a-zA-Z]+]] = getelementptr inbounds %struct.Foo, ptr %[[O]], i32 0, i32 0
// WINDOWS64: %[[LOAD:[0-9a-zA-Z]+]] = load i32, ptr %[[X]]
// WINDOWS64: ret i32 %[[LOAD]]

// WINDOWS64: define dso_local noundef i32 @"?bar@@YAHUFoo@@@Z.sse4.2"(ptr noundef %[[O:[0-9a-zA-Z]+]])
// WINDOWS64: %[[X:[0-9a-zA-Z]+]] = getelementptr inbounds %struct.Foo, ptr %[[O]], i32 0, i32 0
// WINDOWS64: %[[LOAD:[0-9a-zA-Z]+]] = load i32, ptr %[[X]]
// WINDOWS64: %[[ADD:[0-9a-zA-Z]+]] = add nsw i32 %[[LOAD]], 1
// WINDOWS64: ret i32 %[[ADD]]

// WINDOWS64: define dso_local noundef i32 @"?bar@@YAHUFoo@@@Z.arch_ivybridge"(ptr noundef %[[O:[0-9a-zA-Z]+]])
// WINDOWS64: %[[X:[0-9a-zA-Z]+]] = getelementptr inbounds %struct.Foo, ptr %[[O]], i32 0, i32 0
// WINDOWS64: %[[LOAD:[0-9a-zA-Z]+]] = load i32, ptr %[[X]]
// WINDOWS64: %[[ADD:[0-9a-zA-Z]+]] = add nsw i32 %[[LOAD]], 2
// WINDOWS64: ret i32 %[[ADD]]

// WINDOWS64: define dso_local void @"?usage@@YAXXZ"()
// WINDOWS64: %[[F:[0-9a-zA-Z]+]] = alloca %struct.Foo
// WINDOWS64: %[[ARG:[0-9a-zA-Z.]+]] = alloca %struct.Foo
// WINDOWS64: %[[CALL:[0-9a-zA-Z]+]] = call noundef i32 @"?bar@@YAHUFoo@@@Z.resolver"(ptr noundef %[[ARG]])

// WINDOWS64: define weak_odr dso_local i32 @"?bar@@YAHUFoo@@@Z.resolver"(ptr %0)
// WINDOWS64: %[[RET:[0-9a-zA-Z]+]] = musttail call i32 @"?bar@@YAHUFoo@@@Z.arch_ivybridge"(ptr %0)
// WINDOWS64-NEXT: ret i32 %[[RET]]
// WINDOWS64: %[[RET:[0-9a-zA-Z]+]] = musttail call i32 @"?bar@@YAHUFoo@@@Z.sse4.2"(ptr %0)
// WINDOWS64-NEXT: ret i32 %[[RET]]
// WINDOWS64: %[[RET:[0-9a-zA-Z]+]] = musttail call i32 @"?bar@@YAHUFoo@@@Z"(ptr %0)
// WINDOWS64-NEXT: ret i32 %[[RET]]
