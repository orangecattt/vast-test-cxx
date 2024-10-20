// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

extern "C" {
#ifdef __MACH__
#pragma clang section bss = "__BSS,__mybss1" data = "__DATA,__mydata1" rodata = "__RODATA,__myrodata1"
#pragma clang section text = "__TEXT,__mytext1"
#else
#pragma clang section bss="my_bss.1" data="my_data.1" rodata="my_rodata.1"
#pragma clang section text="my_text.1"
#endif
int a;      // my_bss.1
int b = 1;  // my_data.1
int c[4];   // my_bss.1
short d[5] = {0}; // my_bss.1
short e[6] = {0, 0, 1}; // my_data.1
extern const int f;
const int f = 2;  // my_rodata.1
int foo(void) {   // my_text.1
  return b;
}
static int g[2]; // my_bss.1
#pragma clang section bss=""
int h; // default - .bss
#ifdef __MACH__
#pragma clang section data = "" bss = "__BSS,__mybss2" text = "__TEXT,__mytext2"
#else
#pragma clang section data=""  bss="my_bss.2" text="my_text.2"
#endif
int i = 0; // my_bss.2
extern const int j;
const int j = 4; // default - .rodata
int k; // my_bss.2
extern int zoo(int *x, int *y);
int goo(void) {  // my_text.2
  static int lstat_h;  // my_bss.2
  return zoo(g, &lstat_h);
}
#ifdef __MACH__
#pragma clang section rodata = "__RODATA,__myrodata2" data = "__DATA,__mydata2" relro = "__RELRO,__myrelro2"
#else
#pragma clang section rodata="my_rodata.2" data="my_data.2" relro="my_relro.2"
#endif
int l = 5; // my_data.2
extern const int m;
const int m = 6; // my_rodata.2

typedef int (*fptr_t)(void);
const fptr_t fptrs[2] = {&foo, &goo};
#pragma clang section rodata="" data="" bss="" text=""
int n; // default
int o = 6; // default
extern const int p;
const int p = 7; // default
int hoo(void) {
  return b + fptrs[f]();
}
}





