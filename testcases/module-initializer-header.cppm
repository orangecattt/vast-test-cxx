// RUN:  rm -rf %t
// RUN:  split-file %s %t
// RUN: %driver -cc1 %isys -std=c++20 -xc++-user-header -emit-header-unit %t/header.h -o %t/header.pcm
// RUN: %driver -cc1 %isys -std=c++20 -fmodule-file=%t/header.pcm %t/M.cppm %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++20 -fmodule-file=%t/header.pcm %t/Use.cpp %target -o %t%output-suffix && %filecheck
//--- header.h
int foo();
static int i = foo();

//--- M.cppm
module;
import "header.h";
export module M;


//--- Use.cpp
import "header.h";

