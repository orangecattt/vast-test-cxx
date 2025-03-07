// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
extern "C" {

#pragma pack(push, 2)
  typedef struct ABC* abc;

  struct ABCS {
    float red;
    float green;
    float blue;
    float alpha;
  };

  typedef void (*XYZ)();
#pragma pack(pop)
}


union ABCU {
  ABCS color;
  XYZ bg;
};

struct AData {
  ABCU data;
};

class L {
 public:
  L() {}
  L(const L& other);

 private:
  AData fdata;
};


L::L(const L& other)
{
  fdata = other.fdata;
}
