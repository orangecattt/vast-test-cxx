// RUN: %driver -cc1 %isys %s -fblocks %target -o %t%output-suffix && %filecheck
// RUN: %driver -cc1 %isys %s -fno-rtti -fblocks %target -o %t%output-suffix && %filecheck

void func(void*);

struct Test
{
  virtual void use() { func((void*)this); }
  Test(Test&c) { func((void*)this); }
  Test() { func((void*)this); }
};

void useBlock(void (^)(void));

int main (void) {
  __block Test t;
  useBlock(^(void) { t.use(); });
}

