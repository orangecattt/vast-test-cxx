// RUN: %driver -cc1 %isys -std=c++11 %s %target -o %t%output-suffix && %filecheck

extern "C" int printf(...);

int count;

struct S {
  S() : iS (++count) { printf("S::S(%d)\n", iS); }
  ~S() { printf("S::~S(%d)\n", iS); }
  int iS;
};

struct V {
  V() : iV (++count) { printf("V::V(%d)\n", iV); }
  virtual ~V() { printf("V::~V(%d)\n", iV); }
  int iV;
};

struct COST
{
  S *cost;
  V *vcost;
  unsigned *cost_val;

  ~COST();
  COST();
};


COST::COST()
{
  cost = new S[3];
  vcost = new V[4];
  cost_val = new unsigned[10];
}

COST::~COST()
{
  if (cost) {
   delete [] cost;
  }
  if (vcost) {
   delete [] vcost;
  }
  if (cost_val)
    delete [] cost_val;
}

COST c1;

int main()
{
  COST c3;
}
COST c2;


