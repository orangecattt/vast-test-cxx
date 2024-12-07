// RUN: %driver -cc1 %isys -std=c++1z %s %target -o %t%output-suffix && %filecheck

template<int> struct A {};
template<int ...N> void foldr(A<(N + ...)>);
template<int ...N> void foldl(A<(... + N)>);
template<int ...N> void foldr1(A<(N + ... + 1)>);
template<int ...N> void foldl1(A<(1 + ... + N)>);
void use() {
  foldr<1, 2, 3>({});
  foldl<1, 2, 3>({});
  foldr1<1, 2, 3>({});
  foldl1<1, 2, 3>({});
}

template<int ...N> using Foldr = A<(N + ...)>;
template<int ...N> using Foldl = A<(... + N)>;
template<int ...N> using Foldr1 = A<(N + ... + 1)>;
template<int ...N> using Foldl1 = A<(1 + ... + N)>;

template<int ...A> struct Partial {
  template<int ...B> void foldr(Foldr<A..., B..., A..., B...>);
  template<int ...B> void foldl(Foldl<A..., B..., A..., B...>);
  template<int ...B> void foldr1(Foldr1<A..., B..., A..., B...>);
  template<int ...B> void foldl1(Foldl1<A..., B..., A..., B...>);
};
void use(Partial<1, 2> p) {
  p.foldr<3, 4>({});
  p.foldl<3, 4>({});
  p.foldr1<3, 4>({});
  p.foldl1<3, 4>({});
}

extern int n;
template<int ...N> void f() {
  (n = ... = N);
}
template void f<>();
