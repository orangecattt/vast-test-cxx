// Make sure unbounded arrays compile with debug information.
//
// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

// PR1068

struct Object {
  char buffer[];
};

int main(int argc, char** argv) {
  new Object;
  return 0;
}
