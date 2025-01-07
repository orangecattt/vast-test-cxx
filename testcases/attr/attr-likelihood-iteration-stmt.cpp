// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

void wl(int e){
  while(e) [[likely]] ++e;
}

void wu(int e){
  while(e) [[unlikely]] ++e;
}

void w_branch_elided(unsigned e){
  while(1) [[likely]] ++e;
}

void fl(unsigned e)
{
  for(int i = 0; i != e; ++e) [[likely]];
}

void fu(int e)
{
  for(int i = 0; i != e; ++e) [[unlikely]];
}

void f_branch_elided()
{
  for(;;) [[likely]];
}

void frl(int (&&e) [4])
{
  for(int i : e) [[likely]];
}

void fru(int (&&e) [4])
{
  for(int i : e) [[unlikely]];
}
