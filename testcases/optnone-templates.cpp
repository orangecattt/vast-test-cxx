// RUN: %driver -cc1 %isys %s -std=c++11 -disable-O0-optnone %target -o %t%output-suffix && %filecheck



template <typename T> T template_normal(T a)
{
  return a + a;
}

template <typename T> __attribute__((optnone)) T template_optnone(T a)
{
  return a + a + a;
}

int container(int i)
{
  return template_normal<int>(i) + template_optnone<int>(i);
}




template <typename T, typename U> class template_normal_base {
public:
  T method(T t, U u) 
  {
    return t + static_cast<T>(u);
  }
};

template <typename U> class template_normal_base<int, U>
{
public:
  __attribute__((optnone)) int method (int t, U u)
  {
    return t - static_cast<int>(u);
  }
};

void container2() 
{
  int y = 2;
  float z = 3.0;
  template_normal_base<float, int> class_normal;
  template_normal_base<int, float> class_optnone;
  float r1 = class_normal.method(z, y);
  float r2 = class_optnone.method(y, z);
}




template <typename T, typename U> class template_optnone_base {
public:
  __attribute__((optnone)) T method(T t, U u) 
  {
    return t + static_cast<T>(u);
  }
};

template <typename U> class template_optnone_base<int, U>
{
public:
  int method (int t, U u)
  {
    return t - static_cast<int>(u);
  }
};

void container3() 
{
  int y = 2;
  float z = 3.0;
  template_optnone_base<float, int> class_optnone;
  template_optnone_base<int, float> class_normal;
  float r1 = class_optnone.method(z, y);
  float r2 = class_normal.method(y, z);
}



