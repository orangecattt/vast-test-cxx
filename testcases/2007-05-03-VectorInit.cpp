// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

typedef float v4sf __attribute__((vector_size(16)));

typedef v4sf float4;

static float4 splat4(float a)
{
  float4 tmp = {a,a,a,a};
  return tmp;
}

float4 foo(float a)
{
  return splat4(a);
}
