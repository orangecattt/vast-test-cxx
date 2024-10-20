// RUN: %driver -cc1 %isys -std=c++2a -DNOATTR %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++2a %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++2a -DNOATTR -fno-c++-static-destructors %s %target -o %t%output-suffix && %filecheck



class a {
public:
  a();
  ~a();
};
class logger_base {
  a d;
};
class e : logger_base {};
#ifndef NOATTR
__attribute((no_destroy))
#endif
e g;



