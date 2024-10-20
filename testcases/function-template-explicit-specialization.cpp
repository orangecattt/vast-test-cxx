// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

template<typename T> void a(T);
template<> void a(int) {}


namespace X {
template<typename T> void b(T);
template<> void b(int) {}
}

