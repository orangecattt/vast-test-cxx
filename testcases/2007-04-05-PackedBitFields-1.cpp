// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

#ifdef PACKED
#define P __attribute__((packed))
#else
#define P
#endif

struct P M_Packed {
  unsigned int l_Packed;
  unsigned short k_Packed : 6,
    i_Packed : 15,
    j_Packed : 11;

};

struct M_Packed sM_Packed;

int testM_Packed (void) {
  struct M_Packed x;
  return (x.i_Packed != 0);
}
