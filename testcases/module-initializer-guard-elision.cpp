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


//--- O.cpp

export module O;

export int foo ();


//--- P.cpp

export module P;

export import O;
export int bar ();


//--- Q.cpp

export module Q;

export struct Quack {
  Quack(){};
};

export Quack Duck;

export int baz ();


//--- R.cpp

export module R;
export import Q;


//--- S.cpp

export module S;
export import R;


//--- T.cpp
module;
import S;
export module T;


//--- U.cpp
export module U;
module :private;
import T;

