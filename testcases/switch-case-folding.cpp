// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
// CHECK that we don't crash.

int main(void){
	int x = 12;
	// Make sure we don't crash when constant folding the case 4
	// statement due to the case 5 statement contained in the do loop
	switch (4) {
		case 4: do { 
                     switch (6)  {
                       case 6: {
                         case 5: x++;
                       };
                     };
                } while (x < 100);
	}
	return x;
}
