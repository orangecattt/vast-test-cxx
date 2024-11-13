// RUN: %driver -cc1 %isys %std_cxx11- -Wno-dynamic-exception-spec %s %target -o %t%output-suffix && %filecheck

void g();

void f() throw (int) { 

  g();
}

