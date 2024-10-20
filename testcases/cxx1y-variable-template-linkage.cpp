// RUN: %driver -cc1 %isys -std=c++1y %s %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys -std=c++1y -fcxx-exceptions %s %target -o %t%output-suffix && %filecheck


template <typename T> int x = 42;

template <typename T> static int y = 42;

template <typename T> const int z = 42;

template <typename T> T t = 42;

int mode;

static const int &foo() {
   struct Foo { };

   switch (mode) {
   case 0:
     return x<int>;
   case 1:
     return x<Foo>;
   case 2:
     return y<int>;
   case 3:
     return y<Foo>;
   case 4:
     return z<int>;
   case 5:
     return z<Foo>;
   case 6:
     return t<int>;
   case 7:
     return t<const int>;
   }
}


#if !__has_feature(cxx_exceptions) // File A
const int &bar() {
	return foo();
}

#else // File B

const int &bar();

int main() {
	&bar() == &foo() ? throw 0 : (void)0; // Should not throw exception at runtime.
}

#endif // end of Files A and B

