// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck

struct basic_ios{~basic_ios(); };

template<typename _CharT> struct basic_istream : virtual public basic_ios {
  virtual ~basic_istream(){}
};

template<typename _CharT> struct basic_iostream : public basic_istream<_CharT>
{
  virtual ~basic_iostream(){}
};

basic_iostream<char> res;

int main() {
}






