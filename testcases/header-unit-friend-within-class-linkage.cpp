// RUN:  rm -rf %t
// RUN:  split-file %s %t
// RUN: %driver -cc1 %isys -std=c++20 -xc++-user-header -emit-header-unit %t/foo.h -o %t/foo.pcm
// RUN: %driver -cc1 %isys -std=c++20 -fmodule-file=%t/foo.pcm %t/user.cpp %target -o %t%output-suffix && %filecheck

//--- foo.h
class foo {
    int value;
public:
    foo(int v) : value(v) {}

    friend int getFooValue(foo f) {
        return f.value;
    }
};

//--- user.cpp
import "foo.h";
int use() {
    foo f(43);
    return getFooValue(f);
}

