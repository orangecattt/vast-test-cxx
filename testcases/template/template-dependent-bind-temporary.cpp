// RUN: %driver -cc1 %isys %s %target -o %t%output-suffix && %filecheck
struct string {
  string (const string& );
  string ();
  ~string();
};

string operator + (char ch, const string&);

template <class T>
void IntToString(T a)
{
 string result;
 T digit; 
 char((digit < 10 ? '0' : 'a') + digit) + result;
}

int main() {
  IntToString('a');
}

