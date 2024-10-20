// RUN:  rm -rf %t
// RUN:  split-file %s %t
// RUN:  cd %t

// RUN: %driver -cc1 %isys -std=c++20 N.cpp -emit-module-interface -o N.pcm
// RUN: %driver -cc1 %isys -std=c++20 N.pcm %target -o %t%output-suffix && %filecheck

// RUN: %driver -cc1 %isys -std=c++20 O.cpp -emit-module-interface -o O.pcm
// RUN: %driver -cc1 %isys -std=c++20 O.pcm %target -o %t%output-suffix && %filecheck

// RUN: %driver -cc1 %isys -std=c++20 M-Part.cpp -emit-module-interface -o M-Part.pcm
// RUN: %driver -cc1 %isys -std=c++20 M-Part.pcm -emit-module-interface %target -o %t%output-suffix && %filecheck

// RUN: %driver -cc1 %isys -std=c++20 M.cpp -fprebuilt-module-path=%t -emit-module-interface -o M.pcm
// RUN: %driver -cc1 %isys -std=c++20 M.pcm -fprebuilt-module-path=%t %target -o %t%output-suffix && %filecheck

// RUN: %driver -cc1 %isys -std=c++20 useM.cpp -fprebuilt-module-path=%t %target -o %t%output-suffix && %filecheck

// RUN: %driver -cc1 %isys -std=c++20 M-impl.cpp -fprebuilt-module-path=%t %target -o %t%output-suffix && %filecheck

// RUN: %driver -cc1 %isys -std=c++20 N.cpp %target -o %t%output-suffix && %filecheck

// RUN: %driver -cc1 %isys -std=c++20 O.cpp %target -o %t%output-suffix && %filecheck

// RUN: %driver -cc1 %isys -std=c++20 M-Part.cpp %target -o %t%output-suffix && %filecheck

// RUN: %driver -cc1 %isys -std=c++20 M.cpp -fprebuilt-module-path=%t %target -o %t%output-suffix && %filecheck

//--- N-h.h

struct Oink {
  Oink(){};
};

Oink Hog;

//--- N.cpp

module;
#include "N-h.h"

export module N;

export struct Quack {
  Quack(){};
};

export Quack Duck;


//--- O-h.h

struct Meow {
  Meow(){};
};

Meow Cat;

//--- O.cpp

module;
#include "O-h.h"

export module O;

export struct Bark {
  Bark(){};
};

export Bark Dog;


//--- P-h.h

struct Croak {
  Croak(){};
};

Croak Frog;

//--- M-Part.cpp

module;
#include "P-h.h"

module M:Part;

struct Squawk {
  Squawk(){};
};

Squawk parrot;


//--- M-h.h

struct Moo {
  Moo(){};
};

Moo Cow;

//--- M.cpp

module;
#include "M-h.h"

export module M;
import N;
export import O;
import :Part;

export struct Baa {
  int x;
  Baa(){};
  Baa(int x) : x(x) {}
  int getX() { return x; }
};

export Baa Sheep(10);


//--- useM.cpp

import M;

int main() {
  return Sheep.getX();
}


//--- M-impl.cpp

module M;

int foo(int i) { return i + 1; }

