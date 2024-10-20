// RUN: %driver -cc1 %isys -fblocks %s %target -o %t%output-suffix && %filecheck

void * _NSConcreteStackBlock;
#ifdef __cplusplus
extern "C" void exit(int);
#else
extern void exit(int);
#endif

enum numbers {
  zero, one, two, three, four
};

typedef enum numbers (^myblock)(enum numbers);


double test(myblock I) {
  return I(three);
}

int main() {
  __block enum numbers x = one;
  __block enum numbers y = two;

  /* Breakpoint for first Block function.  */
  myblock CL = ^(enum numbers z)
    { enum numbers savex = x;
      { __block enum numbers x = savex;
	y = z;
	if (y != three)
	  exit (6);
	test (
	      /* Breakpoint for second Block function.  */
	      ^ (enum numbers z) {
		if (y != three) {
		  exit(1);
		}
		if (x != one)
		  exit(2);
		x = z;
		if (x != three)
		  exit(3);
		if (y != three)
		  exit(4);
		return (enum numbers) four;
	      });}
      return x;
    };

  enum numbers res = (enum numbers)test(CL);

  if (res != one)
    exit (5);
  return 0;
}
