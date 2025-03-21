
// RUN:  rm -rf %t
// RUN:  split-file %s %t
// RUN:  cd %t
// RUN: %driver -cc1 %isys -std=c++20 -emit-module-interface %t/Mod.cppm -o %t/Mod.pcm
// RUN: %driver -cc1 %isys -std=c++20 %t/Mod.pcm %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++20 -fmodule-file=Mod=%t/Mod.pcm %t/Use.cpp %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++20 -emit-module-interface %t/Mod.cppm -DKEY_FUNCTION_INLINE -o %t/Mod.pcm
// RUN: %driver -cc1 %isys -std=c++20 -emit-module-interface %t/M-A.cppm -o %t/M-A.pcm
// RUN: %driver -cc1 %isys -std=c++20 -fmodule-file=M:A=%t/M-A.pcm %t/M-B.cppm %target -o %t%output-suffix && %filecheck

//--- Mod.cppm
export module Mod;

export class Base {
public:
    virtual ~Base();
};
#ifdef KEY_FUNCTION_INLINE
inline
#endif
Base::~Base() {}



module :private;
int private_use() {
    Base base;
    return 43;
}

//--- Use.cpp
import Mod;
int use() {
    Base* base = new Base();
    return 43;
}




//--- M-A.cppm
export module M:A;
export class C {
public:
    virtual ~C();
};

int a_use() {
    C c;
    return 43;
}

//--- M-B.cppm
export module M:B;
import :A;

C::~C() {}

int b_use() {
    C c;
    return 43;
}

