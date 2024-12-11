
// RUN: %driver -cc1 %isys -std=c++20 %s -emit-module-interface -o %T/HasPMF.pcm
// RUN: %driver -cc1 %isys -std=c++20 %T/HasPMF.pcm %target -o %t%output-suffix && %filecheck

module;

struct Glob {
  Glob(){};
};

Glob G;

export module HasPMF;

export struct InMod {
  InMod(){};
};

export InMod IM;

module :private;

struct InPMF {
  InPMF(){};
};

InPMF P;

