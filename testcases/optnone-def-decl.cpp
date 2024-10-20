// RUN: %driver -cc1 %isys %s -fms-extensions %target -o %t%output-suffix && %filecheck


extern int decl_only(int a) __attribute__((optnone));

int decl_only(int a) {
  return a + a + a + a;
}


extern int def_only(int a);

__attribute__((optnone))
int def_only(int a) {
  return a + a + a + a;
}

int user_of_def_only() {
  return def_only(5);
}


extern int def_and_decl(int a) __attribute__((optnone));

__attribute__((optnone))
int def_and_decl(int a) {
  return a + a + a + a;
}



extern int always_inline_function(int a) __attribute__((always_inline));

__attribute__((optnone))
extern int always_inline_function(int a) {
  return a + a + a + a;
}

int user_of_always_inline_function() {
  return always_inline_function(4);
}


extern int optnone_function(int a) __attribute__((optnone));

__attribute__((always_inline))
int optnone_function(int a) {
  return a + a + a + a;
}

int user_of_optnone_function() {
  return optnone_function(4);
}


extern __forceinline int forceinline_optnone_function(int a, int b);

__attribute__((optnone))
extern int forceinline_optnone_function(int a, int b) {
    return a + b;
}

int user_of_forceinline_optnone_function() {
    return forceinline_optnone_function(4,5);
}


