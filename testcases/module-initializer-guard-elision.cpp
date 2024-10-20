// RUN:  rm -rf %t
// RUN:  split-file %s %t
// RUN:  cd %t

// RUN: %driver -cc1 %isys -std=c++20 O.cpp -emit-module-interface -o O.pcm
// RUN: %driver -cc1 %isys -std=c++20 O.pcm %target -o %t%output-suffix && %filecheck

// RUN: %driver -cc1 %isys -std=c++20 P.cpp -emit-module-interface -fprebuilt-module-path=%t -o P.pcm
// RUN: %driver -cc1 %isys -std=c++20 P.pcm -fprebuilt-module-path=%t %target -o %t%output-suffix && %filecheck

// RUN: %driver -cc1 %isys -std=c++20 Q.cpp -emit-module-interface -o Q.pcm
// RUN: %driver -cc1 %isys -std=c++20 Q.pcm %target -o %t%output-suffix && %filecheck

// RUN: %driver -cc1 %isys -std=c++20 R.cpp -emit-module-interface -fprebuilt-module-path=%t -o R.pcm
// RUN: %driver -cc1 %isys -std=c++20 R.pcm -fprebuilt-module-path=%t %target -o %t%output-suffix && %filecheck

// RUN: %driver -cc1 %isys -std=c++20 S.cpp -emit-module-interface -fprebuilt-module-path=%t -o S.pcm
// RUN: %driver -cc1 %isys -std=c++20 S.pcm -fprebuilt-module-path=%t %target -o %t%output-suffix && %filecheck

// RUN: %driver -cc1 %isys -std=c++20 T.cpp -emit-module-interface -fprebuilt-module-path=%t -o T.pcm
// RUN: %driver -cc1 %isys -std=c++20 T.pcm -fprebuilt-module-path=%t %target -o %t%output-suffix && %filecheck

// RUN: %driver -cc1 %isys -std=c++20 U.cpp -emit-module-interface -fprebuilt-module-path=%t -o U.pcm
// RUN: %driver -cc1 %isys -std=c++20 U.pcm -fprebuilt-module-path=%t %target -o %t%output-suffix && %filecheck

// Testing cases where we can elide the module initializer guard variable.

// This module has no global inits and does not import any other module
//--- O.cpp

export module O;

export int foo ();

// CHECK-O: define void @_ZGIW1O
// CHECK-O-LABEL: entry
// CHECK-O-NEXT: ret void
// CHECK-O-NOT: @_ZGIW1O__in_chrg

// This has no global inits and all the imported modules don't need inits. So
// guard variable is not needed.
//--- P.cpp

export module P;

export import O;
export int bar ();

// CHECK-P: define void @_ZGIW1P
// CHECK-P-LABEL: entry
// CHECK-P-NEXT: ret void
// CHECK-P-NOT: @_ZGIW1P__in_chrg

// This has global inits, so needs a guard.
//--- Q.cpp

export module Q;

export struct Quack {
  Quack(){};
};

export Quack Duck;

export int baz ();

// CHECK-Q: define internal void @__cxx_global_var_init
// CHECK-Q: call {{.*}} @_ZNW1Q5QuackC1Ev
// CHECK-Q: define void @_ZGIW1Q
// CHECK-Q: store i8 1, ptr @_ZGIW1Q__in_chrg
// CHECK-Q: call void @__cxx_global_var_init

// This doesn't have a global init, but it imports a module which needs global
// init, so needs a guard
//--- R.cpp

export module R;
export import Q;

// CHECK-R: define void @_ZGIW1R
// CHECK-R: store i8 1, ptr @_ZGIW1R__in_chrg
// CHECK-R: call{{.*}}@_ZGIW1Q

// This doesn't have a global init and the imported module doesn't have variables needs
// dynamic initialization.
// But the imported module contains modules initialization. So needs a guard.
//--- S.cpp

export module S;
export import R;

// CHECK-S: define void @_ZGIW1S
// CHECK-S: store i8 1, ptr @_ZGIW1S__in_chrg
// CHECK-S: call{{.*}}@_ZGIW1R

// The module itself doesn't have a global init and it doesn't import any module.
// But the global module fragment imports a module that needs an init. So needs a guard.
//--- T.cpp
module;
import S;
export module T;

// CHECK-T: define void @_ZGIW1T
// CHECK-T: store i8 1, ptr @_ZGIW1T__in_chrg
// CHECK-T: call{{.*}}@_ZGIW1S

// The module itself doesn't have a global init and it doesn't import any module.
// But the private module fragment imports a module that needs an init. So needs a guard.
//--- U.cpp
export module U;
module :private;
import T;

// CHECK-U: define void @_ZGIW1U
// CHECK-U: store i8 1, ptr @_ZGIW1U__in_chrg
// CHECK-U: call{{.*}}@_ZGIW1T
