// RUN: %driver -cc1 %isys -std=c++14 -fblocks %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++14 -fblocks -ftrivial-auto-var-init=pattern %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++14 -fblocks -ftrivial-auto-var-init=zero %s %target -o %t%output-suffix && %filecheck

#pragma clang diagnostic ignored "-Winaccessible-base"

#ifdef __x86_64__
char inits[] = {"-86/-21846/-1431655766/i64/-6148914691236517206/-6148914691236517206/i128/-113427455640312821154458202477256070486/i64/-6148914691236517206/AA/"};
#else
char inits[] = {"-1/-1/-1/i32/-1/-1/i32/-1/i32/-1/FF/"};
#define __int128 int;
#endif

template<typename T> void used(T &) noexcept;

#define TEST_UNINIT(NAME, TYPE)                 \
  using type_##NAME = TYPE;                     \
  void test_##NAME##_uninit() {                 \
    type_##NAME uninit;                         \
    used(uninit);                               \
  }

#define TEST_BRACES(NAME, TYPE)                 \
  using type_##NAME = TYPE;                     \
  void test_##NAME##_braces() {                 \
    type_##NAME braces = {};                    \
    used(braces);                               \
  }

#define TEST_CUSTOM(NAME, TYPE, ...)            \
  using type_##NAME = TYPE;                     \
  void test_##NAME##_custom() {                 \
    type_##NAME custom __VA_ARGS__;             \
    used(custom);                               \
  }


struct empty {};
struct small { char c; };
struct smallinit { char c = 42; };
struct smallpartinit { char c = 42, d; };
struct nullinit { char* null = nullptr; };
struct padded { char c; int i; };
struct paddednullinit { char c = 0; int i = 0; };
struct paddedpacked { char c; int i; } __attribute__((packed));
struct paddedpackedarray { struct paddedpacked p[2]; };
struct unpackedinpacked { padded a; char b; } __attribute__((packed));
struct paddednested { struct padded p1, p2; };
struct paddedpackednested { struct paddedpacked p1, p2; };
struct bitfield { int i : 4; int j : 2; };
struct bitfieldaligned { int i : 4; int : 0; int j : 2; };
struct big { unsigned a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s, t, u, v, w, x, y, z; };
struct arraytail { int i; int arr[]; };


struct tailpad { short s; char c; };
struct notlockfree { long long a[4]; };
struct semivolatile { int i; volatile int vi; };
struct semivolatileinit { int i = 0x11111111; volatile int vi = 0x11111111; };
struct base { virtual ~base(); };
struct derived : public base {};
struct virtualderived : public virtual base, public virtual derived {};
union matching { int i; float f; };
union matchingreverse { float f; int i; };
union unmatched { char c; int i; };
union unmatchedreverse { int i; char c; };
union unmatchedfp { float f; double d; };
enum emptyenum {};
enum smallenum { VALUE };

extern "C" {

TEST_UNINIT(char, char);

TEST_BRACES(char, char);

TEST_UNINIT(uchar, unsigned char);

TEST_BRACES(uchar, unsigned char);

TEST_UNINIT(schar, signed char);

TEST_BRACES(schar, signed char);

TEST_UNINIT(wchar_t, wchar_t);

TEST_BRACES(wchar_t, wchar_t);

TEST_UNINIT(short, short);

TEST_BRACES(short, short);

TEST_UNINIT(ushort, unsigned short);

TEST_BRACES(ushort, unsigned short);

TEST_UNINIT(int, int);

TEST_BRACES(int, int);

TEST_UNINIT(unsigned, unsigned);

TEST_BRACES(unsigned, unsigned);

TEST_UNINIT(long, long);

TEST_BRACES(long, long);

TEST_UNINIT(ulong, unsigned long);

TEST_BRACES(ulong, unsigned long);

TEST_UNINIT(longlong, long long);

TEST_BRACES(longlong, long long);

TEST_UNINIT(ulonglong, unsigned long long);

TEST_BRACES(ulonglong, unsigned long long);

TEST_UNINIT(int128, __int128);

TEST_BRACES(int128, __int128);

TEST_UNINIT(uint128, unsigned __int128);

TEST_BRACES(uint128, unsigned __int128);

TEST_UNINIT(fp16, __fp16);

TEST_BRACES(fp16, __fp16);

TEST_UNINIT(float, float);

TEST_BRACES(float, float);

TEST_UNINIT(double, double);

TEST_BRACES(double, double);

TEST_UNINIT(longdouble, long double);

TEST_BRACES(longdouble, long double);

TEST_UNINIT(intptr, int*);

TEST_BRACES(intptr, int*);

TEST_UNINIT(intptrptr, int**);

TEST_BRACES(intptrptr, int**);

TEST_UNINIT(function, void(*)());

TEST_BRACES(function, void(*)());

TEST_UNINIT(bool, bool);

TEST_BRACES(bool, bool);

TEST_UNINIT(empty, empty);

TEST_BRACES(empty, empty);

TEST_UNINIT(small, small);

TEST_BRACES(small, small);

TEST_CUSTOM(small, small, { 42 });

TEST_UNINIT(smallinit, smallinit);

TEST_BRACES(smallinit, smallinit);

TEST_CUSTOM(smallinit, smallinit, { 100 });

TEST_UNINIT(smallpartinit, smallpartinit);

TEST_BRACES(smallpartinit, smallpartinit);

TEST_CUSTOM(smallpartinit, smallpartinit, { 100, 42 });

TEST_UNINIT(nullinit, nullinit);

TEST_BRACES(nullinit, nullinit);

TEST_CUSTOM(nullinit, nullinit, { (char*)"derp" });

TEST_UNINIT(padded, padded);

TEST_BRACES(padded, padded);

TEST_CUSTOM(padded, padded, { 42, 13371337 });

TEST_UNINIT(paddednullinit, paddednullinit);


TEST_BRACES(paddednullinit, paddednullinit);

TEST_CUSTOM(paddednullinit, paddednullinit, { 42, 13371337 });

TEST_UNINIT(paddedpacked, paddedpacked);

TEST_BRACES(paddedpacked, paddedpacked);

TEST_CUSTOM(paddedpacked, paddedpacked, { 42, 13371337 });

TEST_UNINIT(paddedpackedarray, paddedpackedarray);

TEST_BRACES(paddedpackedarray, paddedpackedarray);

TEST_CUSTOM(paddedpackedarray, paddedpackedarray, { {{ 42, 13371337 }, { 43, 13371338 }} });

TEST_UNINIT(unpackedinpacked, unpackedinpacked);

TEST_UNINIT(paddednested, paddednested);

TEST_BRACES(paddednested, paddednested);

TEST_CUSTOM(paddednested, paddednested, { { 42, 13371337 }, { 43, 13371338 } });

TEST_UNINIT(paddedpackednested, paddedpackednested);

TEST_BRACES(paddedpackednested, paddedpackednested);

TEST_CUSTOM(paddedpackednested, paddedpackednested, { { 42, 13371337 }, { 43, 13371338 } });

TEST_UNINIT(bitfield, bitfield);

TEST_BRACES(bitfield, bitfield);

TEST_CUSTOM(bitfield, bitfield, { 4, 1 });

TEST_UNINIT(bitfieldaligned, bitfieldaligned);

TEST_BRACES(bitfieldaligned, bitfieldaligned);

TEST_CUSTOM(bitfieldaligned, bitfieldaligned, { 4, 1  });

TEST_UNINIT(big, big);

TEST_BRACES(big, big);

TEST_CUSTOM(big, big, { 0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA, 0xAAAAAAAA });

TEST_UNINIT(arraytail, arraytail);

TEST_BRACES(arraytail, arraytail);

TEST_CUSTOM(arraytail, arraytail, { 0xdead });

TEST_UNINIT(int0, int[0]);

TEST_BRACES(int0, int[0]);

TEST_UNINIT(int1, int[1]);

TEST_BRACES(int1, int[1]);

TEST_CUSTOM(int1, int[1], { 0x33333333 });

TEST_UNINIT(int64, int[64]);

TEST_BRACES(int64, int[64]);

TEST_CUSTOM(int64, int[64], = { 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111, 0x11111111 });

TEST_UNINIT(bool4, bool[4]);

TEST_BRACES(bool4, bool[4]);

TEST_CUSTOM(bool4, bool[4], { true, true, true, true });

TEST_UNINIT(intptr4, int*[4]);

TEST_BRACES(intptr4, int*[4]);

TEST_CUSTOM(intptr4, int *[4], = {(int *)0x22222222, (int *)0x22222222, (int *)0x22222222, (int *)0x22222222});

TEST_UNINIT(tailpad4, tailpad[4]);

TEST_BRACES(tailpad4, tailpad[4]);

TEST_CUSTOM(tailpad4, tailpad[4], { {257, 1}, {257, 1}, {257, 1}, {257, 1} });

TEST_UNINIT(tailpad9, tailpad[9]);

TEST_BRACES(tailpad9, tailpad[9]);

TEST_CUSTOM(tailpad9, tailpad[9], { {257, 1}, {257, 1}, {257, 1}, {257, 1}, {257, 1}, {257, 1}, {257, 1}, {257, 1}, {257, 1} });

TEST_UNINIT(atomicbool, _Atomic(bool));

TEST_UNINIT(atomicint, _Atomic(int));

TEST_UNINIT(atomicdouble, _Atomic(double));

TEST_UNINIT(atomicnotlockfree, _Atomic(notlockfree));

TEST_UNINIT(atomicpadded, _Atomic(padded));

TEST_UNINIT(atomictailpad, _Atomic(tailpad));

TEST_UNINIT(complexfloat, _Complex float);


TEST_BRACES(complexfloat, _Complex float);

TEST_CUSTOM(complexfloat, _Complex float, { 3.1415926535897932384626433, 3.1415926535897932384626433 });

TEST_UNINIT(complexdouble, _Complex double);

TEST_BRACES(complexdouble, _Complex double);

TEST_CUSTOM(complexdouble, _Complex double, { 3.1415926535897932384626433, 3.1415926535897932384626433 });

TEST_UNINIT(volatileint, volatile int);

TEST_BRACES(volatileint, volatile int);

TEST_UNINIT(semivolatile, semivolatile);

TEST_BRACES(semivolatile, semivolatile);

TEST_CUSTOM(semivolatile, semivolatile, { 0x44444444, 0x44444444 });

TEST_UNINIT(semivolatileinit, semivolatileinit);

TEST_BRACES(semivolatileinit, semivolatileinit);

TEST_CUSTOM(semivolatileinit, semivolatileinit, { 0x44444444, 0x44444444 });

TEST_UNINIT(base, base);

TEST_BRACES(base, base);

TEST_UNINIT(derived, derived);

TEST_BRACES(derived, derived);

TEST_UNINIT(virtualderived, virtualderived);

TEST_BRACES(virtualderived, virtualderived);

TEST_UNINIT(matching, matching);

TEST_BRACES(matching, matching);

TEST_CUSTOM(matching, matching, { .f = 0xf00f });

TEST_UNINIT(matchingreverse, matchingreverse);

TEST_BRACES(matchingreverse, matchingreverse);

TEST_CUSTOM(matchingreverse, matchingreverse, { .i = 0xf00f });

TEST_UNINIT(unmatched, unmatched);

TEST_BRACES(unmatched, unmatched);

TEST_CUSTOM(unmatched, unmatched, { .i = 0x3badbeef });

TEST_UNINIT(unmatchedreverse, unmatchedreverse);

TEST_BRACES(unmatchedreverse, unmatchedreverse);

TEST_CUSTOM(unmatchedreverse, unmatchedreverse, { .c = 42  });

TEST_UNINIT(unmatchedfp, unmatchedfp);

TEST_BRACES(unmatchedfp, unmatchedfp);

TEST_CUSTOM(unmatchedfp, unmatchedfp, { .d = 3.1415926535897932384626433 });

TEST_UNINIT(emptyenum, emptyenum);

TEST_BRACES(emptyenum, emptyenum);

TEST_CUSTOM(emptyenum, emptyenum, { (emptyenum)42 });

TEST_UNINIT(smallenum, smallenum);

TEST_BRACES(smallenum, smallenum);

TEST_CUSTOM(smallenum, smallenum, { (smallenum)42 });

TEST_UNINIT(intvec16, int  __attribute__((vector_size(16))));

TEST_BRACES(intvec16, int  __attribute__((vector_size(16))));

TEST_CUSTOM(intvec16, int  __attribute__((vector_size(16))), { 0x44444444, 0x44444444, 0x44444444, 0x44444444 });

TEST_UNINIT(longlongvec32, long long  __attribute__((vector_size(32))));

TEST_BRACES(longlongvec32, long long  __attribute__((vector_size(32))));

TEST_CUSTOM(longlongvec32, long long  __attribute__((vector_size(32))), { 0x3333333333333333, 0x3333333333333333, 0x3333333333333333, 0x3333333333333333 });

TEST_UNINIT(floatvec16, float  __attribute__((vector_size(16))));

TEST_BRACES(floatvec16, float  __attribute__((vector_size(16))));

TEST_CUSTOM(floatvec16, float  __attribute__((vector_size(16))), { 3.1415926535897932384626433, 3.1415926535897932384626433, 3.1415926535897932384626433, 3.1415926535897932384626433 });

TEST_UNINIT(doublevec32, double  __attribute__((vector_size(32))));

TEST_BRACES(doublevec32, double  __attribute__((vector_size(32))));

TEST_CUSTOM(doublevec32, double  __attribute__((vector_size(32))), { 3.1415926535897932384626433, 3.1415926535897932384626433, 3.1415926535897932384626433, 3.1415926535897932384626433 });

TEST_UNINIT(doublevec24, double  __attribute__((vector_size(24))));

TEST_UNINIT(longdoublevec32, long double  __attribute__((vector_size(sizeof(long double)*2))));

} // extern "C"

